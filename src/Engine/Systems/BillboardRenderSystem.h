#ifndef HYDROGEN_BILLBOARDRENDERSYSTEM_H
#define HYDROGEN_BILLBOARDRENDERSYSTEM_H


#include <string>
#include "glm/vec3.hpp"
#include "IRenderSystem.h"
#include "../Shader.h"
#include "../Camera.h"
#include "../Mesh.h"

namespace Engine::RenderSystems {
    class BillboardRenderSystem : public IRenderSystem {
    private:
    public:
        BillboardRenderSystem(const glm::vec3& _pos, const std::shared_ptr<Engine::Camera>& _camera);

        void Init() override;

        void Update() override;

        void Render() override;

    private:
        std::string path;
        glm::vec3 pos;
        std::unique_ptr<Engine::Mesh> mesh;
        std::unique_ptr<Engine::Shader> shader;
        std::shared_ptr<Engine::Camera> camera;
        glm::vec3 scale = {0.15f, 0.15f, 0.15f};
        glm::vec3 rotate = {0.0f, 0.0f, 0.0f};
        glm::mat4 model;
    };
}


#endif //HYDROGEN_BILLBOARDRENDERSYSTEM_H
