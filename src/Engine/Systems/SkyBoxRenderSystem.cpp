#include "SkyBoxRenderSystem.h"

namespace Engine::RenderSystems {
    SkyBoxRenderSystem::SkyBoxRenderSystem(const std::shared_ptr<Engine::Camera> &_camera) {
        camera = _camera;
    }

    void SkyBoxRenderSystem::Init() {
        shader = std::make_unique<Engine::Shader>("skybox/shader.vert", "skybox/shader.frag");

        auto vertices = std::vector<Vertex>();
        vertices.emplace_back(Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f), glm::vec2(0.0f )});
        vertices.emplace_back(Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f), glm::vec2(0.0f )});
        vertices.emplace_back(Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f), glm::vec2(0.0f )});
        vertices.emplace_back(Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f), glm::vec2(0.0f )});

        vertices.emplace_back(Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0f )});
        vertices.emplace_back(Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0f )});
        vertices.emplace_back(Vertex{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0f )});
        vertices.emplace_back(Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0f )});

        std::vector<unsigned int> indices =
                {
                        // Front face
                        0, 1, 2,
                        2, 3, 0,
                        // Right face
                        1, 5, 6,
                        6, 2, 1,
                        // Back face
                        7, 6, 5,
                        5, 4, 7,
                        // Left face
                        4, 0, 3,
                        3, 7, 4,
                        // Bottom face
                        4, 5, 1,
                        1, 0, 4,
                        // Top face
                        3, 2, 6,
                        6, 7, 3,
                };

        std::vector<Texture> textures = {Texture("TEXTURE_DIFFUSE_0", "./assets/textures/container.jpg")};

        mesh = std::make_unique<Engine::Mesh>(vertices, indices, textures);

        model = glm::mat4(1.0f);
    }

    void SkyBoxRenderSystem::Update() {

    }

    void SkyBoxRenderSystem::Render() {
        shader->use();

        shader->setMatrix4x4("TRANSFORM_IN", camera->getCameraMatrix());
        shader->setMatrix4x4("MODEL_IN", model);

        mesh->Draw(*shader);
    }
} // RenderSystems