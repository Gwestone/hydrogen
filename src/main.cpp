#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <memory>

#include "Shader.h"
#include "BuffersArray_AOS.h"
#include "Camera.h"
#include "Timer.h"
#include "Window.h"
#include "Mesh.h"
#include "Model.h"
#include "Texture.h"
#include "ModelLoader.h"

void processInput(const std::unique_ptr<Window>& window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void onMouseButton( GLFWwindow* window, int button, int action, int mods );

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//timer
auto timer = std::make_unique<Timer>();

//speed
const float speed = 5.0f;

bool rightButtonPressed = false;

int main(){
    // window creation
    // --------------------
    std::unique_ptr<Window> window = std::make_unique<Window>(800, 600, "My window");

    window->setCursorPosCallback(mouse_callback);
    window->setScrollCallback(scroll_callback);
    window->setMouseButtonCallback(onMouseButton);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    stbi_set_flip_vertically_on_load(true);

    // build and compile our shader program
    // ------------------------------------
    auto shader = std::make_shared<Shader>("shader.vert", "shader.frag");

    auto camera = std::make_shared<Camera>(cameraPos, cameraFront, fov, SCR_WIDTH, SCR_HEIGHT);

    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    ModelLoader modelLoader;
    auto models = modelLoader.loadFile("backpack/backpack.obj", shader);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window->get())) {

        //per-frame time logic
        // -----
        timer->calcTime();

        // input
        // -----
        processInput(window);

        //update
        // -----
        camera->updateCamera(cameraPos, cameraFront, fov, SCR_WIDTH, SCR_HEIGHT);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& model : models) {
            model->Draw(camera);
        }

        // draw our first triangle
//        object->Draw(camera);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window->get());
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
//    buffersArray.reset();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(const std::unique_ptr<Window>& window) {
    if (glfwGetKey(window->get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window->get(), true);

    auto cameraSpeed = static_cast<float>(speed * timer->getFrameTime());
    if (glfwGetKey(window->get(), GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += (cameraSpeed * cameraFront);
    if (glfwGetKey(window->get(), GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= (cameraSpeed * cameraFront);
    if (glfwGetKey(window->get(), GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window->get(), GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window->get(), GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += glm::normalize(cameraUp) * cameraSpeed;
    if (glfwGetKey(window->get(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos -= glm::normalize(cameraUp) * cameraSpeed;

}

void onMouseButton(GLFWwindow* window, int button, int action, int mods) {
    if( button == GLFW_MOUSE_BUTTON_RIGHT ) {
        rightButtonPressed = true;
        return;
    }
    rightButtonPressed = false;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    if (rightButtonPressed){
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}