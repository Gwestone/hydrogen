#ifndef HYDROGEN_APP_H
#define HYDROGEN_APP_H


#include "glad/glad.h"
#include <memory>
#include "glm/vec3.hpp"
#include "Window.h"
#include "Timer.h"
#include "stb_image.h"
#include <iostream>
#include "WindowData.h"
#include "glm/geometric.hpp"

namespace Engine{
    class App {
    private:
        void virtual update() = 0;
        void virtual render() = 0;

        void processInput(const std::unique_ptr<Window>& window);
        static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
        static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
        static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    public:
        App();
        ~App();
        void runLoop();
    private:
        std::unique_ptr<Window> window;

        std::string windowName = "My window";
    protected:

        // camera
        WindowData windowData;

        // timer
        std::unique_ptr<Timer> timer;

        // settings
        const unsigned int SCR_WIDTH = 800;
        const unsigned int SCR_HEIGHT = 600;
    };
}

#endif //HYDROGEN_APP_H
