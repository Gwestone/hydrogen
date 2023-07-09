#ifndef HYDROGEN_MYAPP_H
#define HYDROGEN_MYAPP_H


#include "Engine/App.h"
#include "Engine/Shader.h"
#include "Engine/Model.h"

class MyApp : public Engine::App{

    void update() override{
        camera.updateCamera(windowData.cameraPos, windowData.cameraFront, windowData.fov, windowData.width, windowData.height);
    }

    void render() override{
        shader.use();
        shader.setMatrix4x4("TRANSFORM_IN", camera.getCameraMatrix());
        model.Draw(shader);
    }

    Engine::Camera camera;
    Engine::Shader shader;
    Engine::Model model;
public:
    MyApp() : App(){
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        shader = Engine::Shader("shader.vert", "shader.frag");
        camera = Engine::Camera(windowData.cameraPos, windowData.cameraFront, windowData.fov, SCR_WIDTH, SCR_HEIGHT);
        model = Engine::Model("assets/models/backpack/backpack.obj");
    }
};


#endif //HYDROGEN_MYAPP_H
