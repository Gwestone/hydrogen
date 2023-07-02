#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "BuffersArray_AOS.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include "TextureArray.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(){
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    Shader shader("shader.vert", "shader.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };

    float colors[] = {
            1.0f, 0.0f, 0.0f,  // top right
            0.0f, 1.0f, 0.0f,  // bottom right
            1.0f, 0.0f, 0.0f,  // bottom left
            0.0f, 0.0f, 1.0f   // top left
    };

    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

    float uvCoords[] = {
            1.0f, 1.0f,   // top right
            1.0f, 0.0f,  // bottom right
            0.0f, 0.0f,  // bottom left
            0.0f, 1.0f   // top left
    };

    //load and process texture data
    auto* tex1 = new Texture("ourTexture", "container.jpg", GL_RGB);
    auto* tex2 = new Texture("faceTexture", "awesomeface.png", GL_RGBA);
    //end of texture data

    auto* texArray = new TextureArray();
    texArray->addTexture(tex1);
    texArray->addTexture(tex2);

    auto* bufferArray = new BuffersArray_AOS();

    unsigned int vertex_buffer = bufferArray->createBuffer();
    bufferArray->writeBuffer(0, vertex_buffer, vertices, sizeof(vertices), 3);

    unsigned int color_buffer = bufferArray->createBuffer();
    bufferArray->writeBuffer(1, color_buffer, colors, sizeof(colors), 3);

    unsigned int uv_buffer = bufferArray->createBuffer();
    bufferArray->writeBuffer(2, uv_buffer, uvCoords, sizeof(uvCoords), 2);

    bufferArray->createElementBuffer();
    bufferArray->writeElementBuffer(indices, sizeof(indices));

    bufferArray->unbind();

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    texArray->useTextures(shader);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
//        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

        // draw our first triangle
        shader.use();

        texArray->bindAllTextures();
        bufferArray->bind(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    delete bufferArray;

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}