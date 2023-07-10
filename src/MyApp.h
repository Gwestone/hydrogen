#ifndef HYDROGEN_MYAPP_H
#define HYDROGEN_MYAPP_H


#include "Engine/App.h"
#include "Engine/Shader.h"
#include "Engine/Model.h"

class MyApp : public Engine::App{

    void update() override{
        camera->updateCamera(windowData.cameraPos, windowData.cameraFront, windowData.fov, windowData.width, windowData.height);

//        lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;;
//        lightPos.z = sin(glfwGetTime() / 2.0f) * 1.0f;
    }

    void render() override{
        shader->use();
        shader->setVec3("LIGHT_COLOR_IN", lightColor);
        shader->setVec3("LIGHT_POS_IN", lightPos);

        shader->setVec3("CAMERA_POS_IN", camera->getCameraPos());

        shader->setMatrix4x4("TRANSFORM_IN", camera->getCameraMatrix());
        shader->setMatrix4x4("MODEL_IN", model->getModelMatrix());
        model->Draw(*shader);
    }

    std::unique_ptr<Engine::Camera> camera;
    std::unique_ptr<Engine::Shader> shader;
    std::unique_ptr<Engine::Model> model;

    glm::vec3 lightPos = glm::vec3(0, 0, -10);
    glm::vec3 lightColor = glm::vec3(1, 0.5, 1);


public:
    MyApp() : App(){
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//        glEnable(GL_CULL_FACE);
//        glCullFace(GL_FRONT);
//        glFrontFace(GL_CW);

        shader = std::make_unique<Engine::Shader>("base_light/shader.vert", "base_light/shader.frag");
        camera = std::make_unique<Engine::Camera>(windowData.cameraPos, windowData.cameraFront, windowData.fov, SCR_WIDTH, SCR_HEIGHT);
        model = std::make_unique<Engine::Model>("assets/models/backpack/backpack.obj");

//        model->setRotation({0, 0, 0});
    }
};


#endif //HYDROGEN_MYAPP_H
