#include "Log.h"
#include "Core/Base.h"

namespace Engine {

    Ref<spdlog::logger> Log::s_EngineLogger;

    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        Engine::Log::s_EngineLogger = spdlog::stdout_color_mt("HYDROGEN");
        Engine::Log::s_EngineLogger->set_level(spdlog::level::trace);
    }

} // Engine