#include "BaseModelRenderSystem.h"

namespace Engine::RenderSystems {
        void BaseModelRenderSystem::Init() {
            shader = std::make_unique<Engine::Shader>("light/shader.vert", "light/shader.frag");
            model = std::make_unique<Engine::Model>("assets/models/backpack/backpack.obj");
        }

        void BaseModelRenderSystem::Update() {

        }

        void BaseModelRenderSystem::Render() {
            shader->use();

            shader->setFloat("material.shininess", 256.0f);

            shader->setVec3("pointLights[0].position", lightPos);
            shader->setFloat("pointLights[0].constant", 1.0f);
            shader->setFloat("pointLights[0].linear", 0.09f);
            shader->setFloat("pointLights[0].quadratic", 0.032f);
            shader->setVec3("pointLights[0].ambient", lightColor);
            shader->setVec3("pointLights[0].diffuse", lightColor);
            shader->setVec3("pointLights[0].specular", lightColor);

            shader->setVec3("dirLight.position", lightPos);
            shader->setVec3("dirLight.ambient", {0.0f, 0.0f, 0.0f});
            shader->setVec3("dirLight.diffuse", {0.0f, 0.0f, 0.0f});
            shader->setVec3("dirLight.specular", {0.0f, 0.0f, 0.0f});

            shader->setVec3("CAMERA_POS_IN", camera->getCameraPos());

            shader->setMatrix4x4("TRANSFORM_IN", camera->getCameraMatrix());
            shader->setMatrix4x4("MODEL_IN", model->getModelMatrix());
            model->Draw(*shader);
        }

        BaseModelRenderSystem::BaseModelRenderSystem(const std::shared_ptr<Engine::Camera>& _camera) {
            camera = _camera;
        }
    } // RenderSystems