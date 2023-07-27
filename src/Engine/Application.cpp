#include "Application.h"
#include "Event/KeyEvent.h"

namespace Engine{

    Application::Application() {

        Engine::Log::Init();

        HY_ENGINE_INFO("Engine initialization started.");

        eventBus = CreateRef<EventBus>();
        eventBus->setCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        //init timer
        HY_ENGINE_TRACE("Initialization of engine clock.");
        timer = CreateScope<Timer>();

        HY_ENGINE_TRACE("Initialization of main window.");
        window = CreateRef<Window>(SCR_WIDTH, SCR_HEIGHT, windowName);
        window->SetEventBus(eventBus);

        HY_ENGINE_TRACE("Configuration of window.");
        window->setUserPointer(&appData);
        window->setCursorPosCallback(mouse_callback);
        window->setScrollCallback(scroll_callback);
        window->setMouseButtonCallback(onMouseButton);
//        window->hideCursor();

        HY_ENGINE_TRACE("Loading opengl functions.");
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            HY_ENGINE_ERROR("Failed to load opengl functions through glad!");
            exit(EXIT_SUCCESS);
        }

        HY_ENGINE_TRACE("Configuring opengl.");
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        stbi_set_flip_vertically_on_load(true);

        renderSystems = std::vector<Ref<RenderSystems::IRenderSystem>>();

        HY_ENGINE_INFO("Engine initialization completed.");
    }

    Application::~Application() {
        HY_ENGINE_INFO("Engine shutdown started.");
        glfwTerminate();
        exit(EXIT_SUCCESS);
        HY_ENGINE_INFO("Engine shutdown completed.");
    }

    void Application::runLoop() {
        while (!glfwWindowShouldClose(window->getWindow())) {

            //per-frame time logic
            // -----
            timer->calcTime();

            // input
            // -----
            processInput();

            //update
            // -----
            eventBus->DispatchAll();
            update();

            for (const auto& a : renderSystems) {
                a->Update();
            }

            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            render();

            for (const auto& a : renderSystems) {
                a->Render();
            }

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window->getWindow());
            glfwPollEvents();
        }
    }

    void Application::OnEvent(const Scope<Event>& e) {
        if (e->getCategory() == EventCategoryKeyboard and e->getType() == EventType::KeyPressed){
            auto event = dynamic_cast<KeyPressedEvent*>(e.get());
            HandleKeyPressEvent(*event);
        }
    }

    void Application::HandleKeyPressEvent(const KeyPressedEvent &e) {
        auto cameraSpeed = static_cast<float>(appData.speed * timer->getFrameTime());
        using namespace Key;
        switch (e.GetKeyCode()) {
            case Escape:
                glfwSetWindowShouldClose(window->getWindow(), true);
                break;
            case W:
                appData.cameraPos += (cameraSpeed * appData.cameraFront);
                break;
            case S:
                appData.cameraPos -= (cameraSpeed * appData.cameraFront);
                break;
            case A:
                appData.cameraPos -= glm::normalize(glm::cross(appData.cameraFront, appData.cameraUp)) * cameraSpeed;
                break;
            case D:
                appData.cameraPos += glm::normalize(glm::cross(appData.cameraFront, appData.cameraUp)) * cameraSpeed;
                break;
            case Space:
                appData.cameraPos += glm::normalize(appData.cameraUp) * cameraSpeed;
                break;
            case LeftShift:
                appData.cameraPos -= glm::normalize(appData.cameraUp) * cameraSpeed;
                break;
            default:
                HY_ENGINE_INFO("Unidentified key event: {0}");
                break;
        }
    }

    void Application::processInput() {
        #define IF_PRESSED(window, key) glfwGetKey(window->getWindow(), key) == GLFW_PRESS
        #define ADD_KEYPRESS_EVENT(eventBus, key) eventBus->AddEvent(CreateScope<KeyPressedEvent>(key))
        using namespace Key;

        if (IF_PRESSED(window, GLFW_KEY_ESCAPE)){
            ADD_KEYPRESS_EVENT(eventBus, Escape);
        }
        if (IF_PRESSED(window, GLFW_KEY_W)){
            ADD_KEYPRESS_EVENT(eventBus, W);
        }
        if (IF_PRESSED(window, GLFW_KEY_S)){
            ADD_KEYPRESS_EVENT(eventBus, S);
        }
        if (IF_PRESSED(window, GLFW_KEY_A)){
            ADD_KEYPRESS_EVENT(eventBus, A);
        }
        if (IF_PRESSED(window, GLFW_KEY_D)){
            ADD_KEYPRESS_EVENT(eventBus, D);
        }
        if (IF_PRESSED(window, GLFW_KEY_SPACE)){
            ADD_KEYPRESS_EVENT(eventBus, Space);
        }
        if (IF_PRESSED(window, GLFW_KEY_LEFT_SHIFT)){
            ADD_KEYPRESS_EVENT(eventBus, LeftShift);
        }

    }

    void Application::onMouseButton(GLFWwindow *window, int button, int action, int mods) {

        auto* data = (ApplicationData*)glfwGetWindowUserPointer(window );

        if( button == GLFW_MOUSE_BUTTON_RIGHT and (action == GLFW_PRESS or action == GLFW_REPEAT)) {
            data->rightButtonPressed = true;
            return;
        } else if (button == GLFW_MOUSE_BUTTON_RIGHT and action == GLFW_RELEASE){
            data->rightButtonPressed = false;
        }
    }

    void Application::mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {

        auto* data = (ApplicationData*)glfwGetWindowUserPointer(window );

        //TODO make real hold detection system
        if (data->rightButtonPressed){
            float xpos = static_cast<float>(xposIn);
            float ypos = static_cast<float>(yposIn);

            if (data->firstMouse)
            {
                data->lastX = xpos;
                data->lastY = ypos;
                data->firstMouse = false;
            }

            float xoffset = xpos - data->lastX;
            float yoffset = data->lastY - ypos; // reversed since y-coordinates go from bottom to top
            data->lastX = xpos;
            data->lastY = ypos;

            float sensitivity = 0.1f; // change this value to your liking
            xoffset *= sensitivity;
            yoffset *= sensitivity;

            data->yaw += xoffset;
            data->pitch += yoffset;

            // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (data->pitch > 89.0f)
                data->pitch = 89.0f;
            if (data->pitch < -89.0f)
                data->pitch = -89.0f;

            glm::vec3 front;
            front.x = cos(glm::radians(data->yaw)) * cos(glm::radians(data->pitch));
            front.y = sin(glm::radians(data->pitch));
            front.z = sin(glm::radians(data->yaw)) * cos(glm::radians(data->pitch));
            data->cameraFront = glm::normalize(front);
        } else{
            data->lastX = static_cast<float>(xposIn);
            data->lastY = static_cast<float>(yposIn);
        }
    }


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
    void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

        auto* data = (ApplicationData*)glfwGetWindowUserPointer(window );

        data->fov -= (float)yoffset;
        if (data->fov < 1.0f)
            data->fov = 1.0f;
        if (data->fov > 45.0f)
            data->fov = 45.0f;
    }

    void Application::addRenderSystem(Ref<RenderSystems::IRenderSystem> renderSystem) {
        renderSystem->Init();
        renderSystems.push_back(std::move(renderSystem));
    }
}