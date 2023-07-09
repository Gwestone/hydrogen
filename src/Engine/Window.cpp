#include "Window.h"
#include "WindowData.h"

namespace Engine{

    void Window::init() {

        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // glfw window creation
        // --------------------
        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        if (window == nullptr) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
    }

    void Window::setFlags() {
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);
    }


    Window::Window(int _width, int _height, const std::string& _name): width(_width), height(_height), name(_name) {
        init();
        setFlags();
    }

    Window::~Window() {
        glfwTerminate();
    }

    GLFWwindow *Window::get() {
        return window;
    }

    void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height) {

        auto* data = (WindowData*)glfwGetWindowUserPointer( window );

        data->width = width;
        data->height = height;

        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    void Window::setUserPointer(WindowData* data) {
        glfwSetWindowUserPointer(window, data);
    }

    void Window::setScrollCallback(GLFWscrollfun callback) {
        glfwSetScrollCallback(window, callback);
    }

    void Window::setCursorPosCallback(GLFWcursorposfun callback) {
        glfwSetCursorPosCallback(window, callback);
    }

    void Window::setMouseButtonCallback(GLFWmousebuttonfun callback) {
        glfwSetMouseButtonCallback(window, callback);
    }
}
