#include <memory>
#include "BillboardRenderSystem.h"
#include "../Shader.h"

namespace Engine::RenderSystems {

    BillboardRenderSystem::BillboardRenderSystem(const glm::vec3& _pos, const std::shared_ptr<Engine::Camera>& _camera) {
        pos = _pos;
        camera = _camera;
    }

    void BillboardRenderSystem::Init() {
        shader = std::make_unique<Engine::Shader>("billboard/shader.vert", "billboard/shader.frag");

        auto vertices = std::vector<Vertex>();
        vertices.emplace_back(Vertex{glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f, 0.0f)});
        vertices.emplace_back(Vertex{glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f)});
        vertices.emplace_back(Vertex{glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f)});
        vertices.emplace_back(Vertex{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f)});

        std::vector<unsigned int> indices = {1, 2, 3, 2, 1, 0};

        std::vector<Texture> textures = {};

        mesh = std::make_unique<Engine::Mesh>(vertices, indices, textures);

        model = glm::mat4(1.0f);
    }

    void BillboardRenderSystem::Update() {
        model = glm::mat4(1.0f);
        model = glm::scale(model, scale);
        //rotate x
        model = glm::rotate(model, rotate.x, {1, 0, 0});
        //rotate y
        model = glm::rotate(model, rotate.y, {0, 1, 0});
        //rotate z
        model = glm::rotate(model, rotate.z, {0, 0, 1});

        model = glm::translate(model, pos);
    }

    void BillboardRenderSystem::Render() {
        shader->use();

//        shader->setVec3("POSITION_IN", pos);
        shader->setMatrix4x4("TRANSFORM_IN", camera->getCameraMatrix());
        shader->setMatrix4x4("MODEL_IN", model);
//        shader->setMatrix4x4("VIEW_IN", camera->getViewMatrix());

        mesh->Draw(*shader);
    }
}