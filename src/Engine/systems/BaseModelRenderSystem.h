#ifndef HYDROGEN_BASEMODELRENDERSYSTEM_H
#define HYDROGEN_BASEMODELRENDERSYSTEM_H

#include "IRenderSystem.h"
#include "../Shader.h"
#include "../Model.h"

namespace Engine::RenderSystems {

    class BaseModelRenderSystem : public RenderSystems::IRenderSystem{
    public:
        BaseModelRenderSystem(const std::shared_ptr<Engine::Camera>& _camera);

        void Init() override;

        void Update() override;

        void Render() override;
    private:
        std::shared_ptr<Engine::Camera> camera;
        std::unique_ptr<Engine::Shader> shader;
        std::unique_ptr<Engine::Model> model;

        glm::vec3 lightPos = glm::vec3(2, 2, 2);
        glm::vec3 lightColor = glm::vec3(1, 0.5, 1);
    };

} // RenderSystems

#endif //HYDROGEN_BASEMODELRENDERSYSTEM_H
