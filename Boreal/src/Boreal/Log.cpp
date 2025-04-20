#include "bopch.h"
#include "Log.h"

namespace Boreal {

	std::shared_ptr<Pinelog::Logger> Log::s_EngineLogger;
	std::shared_ptr<Pinelog::Logger> Log::s_ClientLogger;

	Log::Log()
	{}

	void Log::Init()
	{
		s_EngineLogger = std::make_shared<Pinelog::Logger>();
		s_ClientLogger = std::make_shared<Pinelog::Logger>();

		s_EngineLogger->setLoggerName("BOREAL");
		s_ClientLogger->setLoggerName("APP");
	}

}