#ifndef HYDROGEN_MYAPP_H
#define HYDROGEN_MYAPP_H


#include "Engine/Application.h"
#include "Engine/Shader.h"
#include "Engine/Model.h"
#include "Engine/Systems/ImguiRenderSystem.h"
#include "Engine/Systems/BaseModelRenderSystem.h"
#include "Engine/Systems/BillboardRenderSystem.h"
#include "Engine/Systems/SkyBoxRenderSystem.h"
#include "Engine/Core/Base.h"

using namespace Engine;

class MyApp : public Application{

    void update() override{
        camera->updateCamera(windowData.cameraPos, windowData.cameraFront, windowData.fov, windowData.width, windowData.height);
    }

    void render() override{

    }

    Ref<Camera> camera;


public:
    MyApp() : Application(){

        camera = CreateRef<Camera>(windowData.cameraPos, windowData.cameraFront, windowData.fov, SCR_WIDTH, SCR_HEIGHT);

        this->addRenderSystem(CreateRef<RenderSystems::BaseModelRenderSystem>(camera));
        this->addRenderSystem(CreateRef<RenderSystems::BillboardRenderSystem>(glm::vec3(2, 2, 2), camera));
//        this->addRenderSystem(CreateRef<Engine::RenderSystems::SkyBoxRenderSystem>(camera)));
        this->addRenderSystem(CreateRef<RenderSystems::ImguiRenderSystem>(window));
    }
};


#endif //HYDROGEN_MYAPP_H
