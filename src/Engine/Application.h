#ifndef HYDROGEN_APPLICATION_H
#define HYDROGEN_APPLICATION_H

#include "include.h"

#include "Window.h"
#include "Timer.h"
#include "WindowData.h"
#include "EngineConfig.h"
#include "Log.h"
#include "Systems/IRenderSystem.h"
#include "Core/Base.h"

namespace Engine{
    class Application {
    private:
        void virtual update() = 0;
        void virtual render() = 0;

        void processInput();
        static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
        static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
        static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    public:
        Application();
        ~Application();
        void runLoop();
    private:

        std::string windowName = "My window";
    protected:

        // camera
        WindowData windowData;

        // timer
        Scope<Timer> timer;

        //config
        EngineConfig config;

        // settings
        const unsigned int SCR_WIDTH = 800;
        const unsigned int SCR_HEIGHT = 600;
        Ref<Window> window;
        std::vector<Ref<RenderSystems::IRenderSystem>> renderSystems;

        void addRenderSystem(Ref<RenderSystems::IRenderSystem> renderSystem);
    };
}

#endif //HYDROGEN_APPLICATION_H
