#ifndef HYDROGEN_WINDOW_H
#define HYDROGEN_WINDOW_H


#include <GLFW/glfw3.h>

class Window {
private:
    void init();
    void setFlags();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
public:
    Window(int _width, int _height, const std::string& _name);
    ~Window();
    GLFWwindow* get();
    void setScrollCallback(GLFWscrollfun callback);
    void setCursorPosCallback(GLFWcursorposfun callback);
    void setMouseButtonCallback(GLFWmousebuttonfun callback);
private:
    GLFWwindow* window;
    int width, height;
    std::string name;
};


#endif //HYDROGEN_WINDOW_H
