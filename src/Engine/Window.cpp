#include "Window.h"
#include "Log.h"
#include "Core/Base.h"

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
            HY_ENGINE_ERROR("Failed to create GLFW window");
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

    GLFWwindow *Window::getWindow() {
        return window;
    }

    void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height) {

        auto* data = (ApplicationData*)glfwGetWindowUserPointer(window );

        data->width = width;
        data->height = height;

        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    void Window::setUserPointer(ApplicationData* data) {
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

    void Window::hideCursor() {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void Window::SetEventBus(const Ref<EventBus>& _eventBus) {
        eventBus = _eventBus;
    }
}
