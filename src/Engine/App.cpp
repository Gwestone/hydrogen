#include "App.h"

namespace Engine{

    App::App() {

        Engine::Log::Init();

        HY_ENGINE_INFO("Engine initialization started.");

        //init timer
        HY_ENGINE_TRACE("Initialization of engine clock.");
        timer = std::make_unique<Timer>();

        HY_ENGINE_TRACE("Initialization of main window.");
        window = std::make_unique<Window>(SCR_WIDTH, SCR_HEIGHT, windowName);

        HY_ENGINE_TRACE("Configuration of window.");
        window->setUserPointer(&windowData);
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

        stbi_set_flip_vertically_on_load(true);

        HY_ENGINE_INFO("Engine initialization completed.");
    }

    App::~App() {
        HY_ENGINE_INFO("Engine shutdown started.");
        glfwTerminate();
        exit(EXIT_SUCCESS);
        HY_ENGINE_INFO("Engine shutdown completed.");
    }

    void App::runLoop() {
        while (!glfwWindowShouldClose(window->getWindow())) {

            //per-frame time logic
            // -----
            timer->calcTime();

            // input
            // -----
            processInput(window);

            //update
            // -----
            update();
//        camera.updateCamera(cameraPos, cameraFront, fov, SCR_WIDTH, SCR_HEIGHT);

            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        shader.use();
//        shader.setMatrix4x4("TRANSFORM_IN", camera.getCameraMatrix());
//        model.Draw(shader);

            render();

            // draw our first triangle
//        object->Draw(camera);

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window->getWindow());
            glfwPollEvents();
        }
    }

    void App::processInput(const std::unique_ptr<Window> &window) {
        if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window->getWindow(), true);

        auto cameraSpeed = static_cast<float>(windowData.speed * timer->getFrameTime());
        if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
            windowData.cameraPos += (cameraSpeed * windowData.cameraFront);
        if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
            windowData.cameraPos -= (cameraSpeed * windowData.cameraFront);
        if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
            windowData.cameraPos -= glm::normalize(glm::cross(windowData.cameraFront, windowData.cameraUp)) * cameraSpeed;
        if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
            windowData.cameraPos += glm::normalize(glm::cross(windowData.cameraFront, windowData.cameraUp)) * cameraSpeed;
        if (glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
            windowData.cameraPos += glm::normalize(windowData.cameraUp) * cameraSpeed;
        if (glfwGetKey(window->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            windowData.cameraPos -= glm::normalize(windowData.cameraUp) * cameraSpeed;

    }

    void App::onMouseButton(GLFWwindow *window, int button, int action, int mods) {

        auto* data = (WindowData*)glfwGetWindowUserPointer( window );

        if( button == GLFW_MOUSE_BUTTON_RIGHT ) {
            data->rightButtonPressed = true;
            return;
        }
        data->rightButtonPressed = false;
    }

    void App::mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {

        auto* data = (WindowData*)glfwGetWindowUserPointer( window );

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
    void App::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

        auto* data = (WindowData*)glfwGetWindowUserPointer( window );

        data->fov -= (float)yoffset;
        if (data->fov < 1.0f)
            data->fov = 1.0f;
        if (data->fov > 45.0f)
            data->fov = 45.0f;
    }
}