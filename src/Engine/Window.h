#ifndef HYDROGEN_WINDOW_H
#define HYDROGEN_WINDOW_H

#include "include.h"
#include "ApplicationData.h"
#include "Event/Event.h"
#include "Core/Base.h"

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
        void setUserPointer(ApplicationData *data);

        void SetEventBus(const Ref<EventBus>& _eventBus);

        void hideCursor();

    private:
        GLFWwindow* window;
        int width, height;
        std::string name;
        Ref<EventBus> eventBus;
    };
}


#endif //HYDROGEN_WINDOW_H
