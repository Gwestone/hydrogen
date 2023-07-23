#ifndef HYDROGEN_MYAPP_H
#define HYDROGEN_MYAPP_H


#include "Engine/App.h"
#include "Engine/Shader.h"
#include "Engine/Model.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Engine/systems/ImguiRenderSystem.h"
#include "Engine/systems/BaseModelRenderSystem.h"

class MyApp : public Engine::App{

    void update() override{
        camera->updateCamera(windowData.cameraPos, windowData.cameraFront, windowData.fov, windowData.width, windowData.height);

//        lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
//        lightPos.z = sin(glfwGetTime() / 2.0f) * 1.0f;
    }

    void render() override{

    }

    std::shared_ptr<Engine::Camera> camera;
    std::unique_ptr<Engine::Shader> shader;
    std::unique_ptr<Engine::Model> model;

    glm::vec3 lightPos = glm::vec3(0, 0, -14);
    glm::vec3 lightColor = glm::vec3(1, 0.5, 1);


public:
    MyApp() : App(){

        camera = std::make_shared<Engine::Camera>(windowData.cameraPos, windowData.cameraFront, windowData.fov, SCR_WIDTH, SCR_HEIGHT);

        this->addRenderSystem(std::make_unique<Engine::RenderSystems::BaseModelRenderSystem>(camera));
        this->addRenderSystem(std::make_unique<Engine::RenderSystems::ImguiRenderSystem>(window));

//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//        glEnable(GL_CULL_FACE);
//        glCullFace(GL_FRONT);
//        glFrontFace(GL_CW);

//        shader = std::make_unique<Engine::Shader>("light/shader.vert", "light/shader.frag");
//        model = std::make_unique<Engine::Model>("assets/models/backpack/backpack.obj");

//        model->setRotation({0, 0, 0});
    }
};


#endif //HYDROGEN_MYAPP_H
