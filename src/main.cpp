#include "MyApp.h"
#include "Engine/Log.h"

int main(){

    auto* app = new MyApp();
    app->runLoop();

    return 0;
}