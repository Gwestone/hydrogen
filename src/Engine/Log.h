#ifndef HYDROGEN_LOG_H
#define HYDROGEN_LOG_H

#include "include.h"

#define HY_ENGINE_TRACE(...) ::Engine::Log::getEngineLogger()->trace(__VA_ARGS__)
#define HY_ENGINE_INFO(...) ::Engine::Log::getEngineLogger()->info(__VA_ARGS__)
#define HY_ENGINE_WARN(...) ::Engine::Log::getEngineLogger()->warn(__VA_ARGS__)
#define HY_ENGINE_ERROR(...) ::Engine::Log::getEngineLogger()->error(__VA_ARGS__)

namespace Engine {

    class Log {
    private:
    public:
        static void Init();
        static std::shared_ptr<spdlog::logger>& getEngineLogger() { return s_EngineLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_EngineLogger;
    };

} // Engine

#endif //HYDROGEN_LOG_H
