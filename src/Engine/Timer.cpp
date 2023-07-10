#include "Timer.h"
#include "Log.h"


namespace Engine{
    Timer::Timer() {
        // timing
        frameTime = 0.0f;	// time between current frame and last frame
        lastFrameTime = 0.0f;
    }

    void Timer::calcTime() {
        float currentTime = static_cast<float>(glfwGetTime());
        frameTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;
    }

    float Timer::getFrameTime() {
        return frameTime;
    }
}