#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include "TextureArray.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <memory>

#include "Shader.h"
#include "BuffersArray_AOS.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(const std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)>& window);
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

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

bool rightButtonPressed = false;
bool leftButtonPressed = false;

int main(){
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> window(glfwCreateWindow(800, 600, "My Window", nullptr, nullptr), glfwDestroyWindow);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window.get());
    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);
    glfwSetCursorPosCallback(window.get(), mouse_callback);
    glfwSetScrollCallback(window.get(), scroll_callback);
    glfwSetMouseButtonCallback(window.get(), onMouseButton);

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
    // vertex shader
    auto shader = std::make_unique<Shader>("shader.vert", "shader.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            -1.0, -1.0, 1.0, //0
            1.0, -1.0, 1.0, //1
            -1.0, 1.0, 1.0, //2
            1.0, 1.0, 1.0, //3
            -1.0, -1.0, -1.0, //4
            1.0, -1.0, -1.0, //5
            -1.0, 1.0, -1.0, //6
            1.0, 1.0, -1.0  //7
    };

    unsigned int indices[] = {
            // note that we start from 0!
            2, 6, 7,
            2, 3, 7,

            //Bottom
            0, 4, 5,
            0, 1, 5,

            //Left
            0, 2, 6,
            0, 4, 6,

            //Right
            1, 3, 7,
            1, 5, 7,

            //Front
            0, 2, 3,
            0, 1, 3,

            //Back
            4, 6, 7,
            4, 5, 7
    };

    float uvCoords[] = {
            0.0f, 0.0f,   // top right
            1.0f, 0.0f,  // bottom right
            1.0f, 0.0f,  // bottom left
            1.0f, 1.0f,   // top left
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
    };

    //load and process texture data
    auto tex1 = std::make_shared<Texture>("ourTexture", "container.jpg", GL_RGB);
    auto tex2  = std::make_shared<Texture>("faceTexture", "awesomeface.png", GL_RGBA);
    //end of texture data

    auto texArray = std::make_unique<TextureArray>();
    texArray->addTexture(tex1);
    texArray->addTexture(tex2);

    auto bufferArray = std::make_unique<BuffersArray_AOS>();

    unsigned int vertex_buffer = bufferArray->createBuffer();
    bufferArray->writeBuffer(0, vertex_buffer, vertices, sizeof(vertices), 3);

    unsigned int uv_buffer = bufferArray->createBuffer();
    bufferArray->writeBuffer(1, uv_buffer, uvCoords, sizeof(uvCoords), 2);

    bufferArray->createElementBuffer();
    bufferArray->writeElementBuffer(indices, sizeof(indices));

    bufferArray->unbind();

    auto camera = std::make_unique<Camera>(cameraPos, cameraFront, fov, SCR_WIDTH, SCR_HEIGHT);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    texArray->useTextures(shader.get());

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window.get())) {
        //per-frame time logic
        // -----

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        //update
        // -----
//        model = glm::rotate(model, (float)glm::sin(glfwGetTime()) * glm::radians(1.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(fov), ((float)SCR_WIDTH / (float)SCR_HEIGHT), 0.1f, 100.0f);

        camera->updateCamera(cameraPos, cameraFront, fov, SCR_WIDTH, SCR_HEIGHT);

        glm::mat4 trans = camera->getCameraMatrix() * model;

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

        // draw our first triangle
        shader->use();
        shader->setMatrix4x4("transform", trans);

        texArray->bindAllTextures();
        bufferArray->bind(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    bufferArray.reset();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(const std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)>& window)
{
    if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.get(), true);

    auto cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += (cameraSpeed * cameraFront);
    if (glfwGetKey(window.get(), GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= (cameraSpeed * cameraFront);
    if (glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

}

void onMouseButton(GLFWwindow* window, int button, int action, int mods) {
    if( button == GLFW_MOUSE_BUTTON_RIGHT ) {
        rightButtonPressed = true;
        return;
    }
    else if( button == GLFW_MOUSE_BUTTON_LEFT ) {
        leftButtonPressed = true;
        return;
    }
    rightButtonPressed = false;
    leftButtonPressed = false;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
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
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}