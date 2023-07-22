#ifndef HYDROGEN_WINDOW_H
#define HYDROGEN_WINDOW_H

#include "include.h"
#include "WindowData.h"

namespace Engine{
    class Window {
    private:
        void init();
        void setFlags();
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    public:
        Window(int _width, int _height, const std::string& _name);
        ~Window();
        GLFWwindow* getWindow();

        void setScrollCallback(GLFWscrollfun callback);
        void setCursorPosCallback(GLFWcursorposfun callback);
        void setMouseButtonCallback(GLFWmousebuttonfun callback);
        void setUserPointer(WindowData *data);

        void hideCursor();

    private:
        GLFWwindow* window;
        int width, height;
        std::string name;
    };
}


#endif //HYDROGEN_WINDOW_H
