#ifndef HYDROGEN_TIMER_H
#define HYDROGEN_TIMER_H

#include <GLFW/glfw3.h>

namespace Engine{
    class Timer {
    private:
    public:
        Timer();
        void calcTime();
        float getFrameTime();
    private:
        float frameTime;
        float lastFrameTime;
    };
}


#endif //HYDROGEN_TIMER_H
