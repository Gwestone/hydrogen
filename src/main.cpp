#include "MyApp.h"
#include "Engine/Log.h"
#include "Engine/Log.h"

int main(){

    Engine::Log::Init();
    HY_ENGINE_INFO("Hello world!");

    auto* app = new MyApp();
    app->runLoop();

    return 0;
}