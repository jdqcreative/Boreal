#pragma once

#include "../../vendor/pinelog/Logger.h"

namespace Boreal {

	class Log
	{
	public:
		Log();

		static void Init();

		inline static std::shared_ptr<Pinelog::Logger>& GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<Pinelog::Logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<Pinelog::Logger> s_EngineLogger;
		static std::shared_ptr<Pinelog::Logger> s_ClientLogger;

	};

}

// Engine logging macros
#define BO_ENGINE_TRACE(...)	::Boreal::Log::GetEngineLogger()->debug(__VA_ARGS__)
#define BO_ENGINE_INFO(...)		::Boreal::Log::GetEngineLogger()->info(__VA_ARGS__)
#define BO_ENGINE_WARN(...)		::Boreal::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define BO_ENGINE_ERROR(...)	::Boreal::Log::GetEngineLogger()->error(__VA_ARGS__)

// Client logging macros
#define BO_TRACE(...)	::Boreal::Log::GetClientLogger()->debug(__VA_ARGS__)
#define BO_INFO(...)		::Boreal::Log::GetClientLogger()->info(__VA_ARGS__)
#define BO_WARN(...)		::Boreal::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BO_ERROR(...)	::Boreal::Log::GetClientLogger()->error(__VA_ARGS__)