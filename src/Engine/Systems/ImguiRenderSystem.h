#ifndef HYDROGEN_IMGUIRENDERSYSTEM_H
#define HYDROGEN_IMGUIRENDERSYSTEM_H

#include "IRenderSystem.h"
#include "../Window.h"

namespace Engine::RenderSystems {

    class ImguiRenderSystem : public IRenderSystem {
    private:
    public:
        ImguiRenderSystem(const std::shared_ptr<Window>& _window);

        void Init() override;

        void Update() override;

        void Render() override;
    private:
        std::shared_ptr<Window> window;
    };

}


#endif //HYDROGEN_IMGUIRENDERSYSTEM_H
