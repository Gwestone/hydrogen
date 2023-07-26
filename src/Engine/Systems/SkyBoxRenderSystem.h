#ifndef HYDROGEN_SKYBOXRENDERSYSTEM_H
#define HYDROGEN_SKYBOXRENDERSYSTEM_H

#include <memory>
#include "IRenderSystem.h"
#include "../Camera.h"
#include "../Shader.h"
#include "../Model.h"

namespace Engine::RenderSystems {

        class SkyBoxRenderSystem : public IRenderSystem{
        public:
            SkyBoxRenderSystem(const std::shared_ptr<Engine::Camera>& _camera);

            void Init() override;

            void Update() override;

            void Render() override;
        private:
            std::shared_ptr<Engine::Camera> camera;
            std::unique_ptr<Engine::Shader> shader;
            std::unique_ptr<Engine::Mesh> mesh;
            glm::vec3 scale = {0.15f, 0.15f, 0.15f};
            glm::vec3 rotate = {0.0f, 0.0f, 0.0f};
            glm::mat4 model;
        };

    } // RenderSystems

#endif //HYDROGEN_SKYBOXRENDERSYSTEM_H
