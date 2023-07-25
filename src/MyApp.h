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
#include "Engine/systems/BillboardRenderSystem.h"
#include "Engine/systems/SkyBoxRenderSystem.h"

class MyApp : public Engine::App{

    void update() override{
        camera->updateCamera(windowData.cameraPos, windowData.cameraFront, windowData.fov, windowData.width, windowData.height);
    }

    void render() override{

//        shader->use();
//        shader->setVec3("LIGHT_COLOR_IN", lightColor);
//        shader->setVec3("LIGHT_POS_IN", lightPos);
//        shader->setVec3("LIGHT_DIRECTION", lightPos);
//
//        shader->setFloat("material.shininess", 256.0f);
//
//        shader->setVec3("pointLights[0].position", lightPos);
//        shader->setFloat("pointLights[0].constant", 1.0f);
//        shader->setFloat("pointLights[0].linear", 0.09f);
//        shader->setFloat("pointLights[0].quadratic", 0.032f);
//        shader->setVec3("pointLights[0].ambient", lightColor);
//        shader->setVec3("pointLights[0].diffuse", lightColor);
//        shader->setVec3("pointLights[0].specular", lightColor);
//
//        shader->setVec3("dirLight.position", lightPos);
//        shader->setVec3("dirLight.ambient", lightColor);
//        shader->setVec3("dirLight.diffuse", lightColor);
//        shader->setVec3("dirLight.specular", lightColor);
//
//        shader->setVec3("CAMERA_POS_IN", camera->getCameraPos());
//
//        shader->setMatrix4x4("TRANSFORM_IN", camera->getCameraMatrix());
//        shader->setMatrix4x4("MODEL_IN", model->getModelMatrix());
//        model->Draw(*shader);
    }

    std::shared_ptr<Engine::Camera> camera;


public:
    MyApp() : App(){

        camera = std::make_shared<Engine::Camera>(windowData.cameraPos, windowData.cameraFront, windowData.fov, SCR_WIDTH, SCR_HEIGHT);

//        this->addRenderSystem(std::move(std::make_unique<Engine::RenderSystems::BaseModelRenderSystem>(camera)));
//        this->addRenderSystem(std::move(std::make_unique<Engine::RenderSystems::BillboardRenderSystem>(glm::vec3(2, 2, 2), camera)));
        this->addRenderSystem(std::move(std::make_unique<Engine::RenderSystems::SkyBoxRenderSystem>(camera)));
        this->addRenderSystem(std::move(std::make_unique<Engine::RenderSystems::ImguiRenderSystem>(window)));

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
