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

        std::vector<Texture> textures = {Texture("TEXTURE_DIFFUSE_0", "./assets/textures/bulb.png")};

        mesh = std::make_unique<Engine::Mesh>(vertices, indices, textures);

        model = glm::mat4(1.0f);
    }

    void BillboardRenderSystem::Update() {

        glm::vec3 direction = glm::normalize(camera->getCameraPos() - pos);

        glm::vec3 up(0.0f, 1.0f, 0.0f);
        glm::vec3 right = glm::normalize(glm::cross(up, direction));

        up = glm::normalize(glm::cross(direction, right));

        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), pos);

        glm::mat4 rotationMatrix(
                glm::vec4(right, 0.0f),
                glm::vec4(up, 0.0f),
                glm::vec4(direction, 0.0f),
                glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
        );

        model = translationMatrix * rotationMatrix * scaleMatrix;

    }

    void BillboardRenderSystem::Render() {
        shader->use();

        shader->setMatrix4x4("TRANSFORM_IN", camera->getCameraMatrix());
        shader->setMatrix4x4("MODEL_IN", model);

        mesh->Draw(*shader);
    }
}