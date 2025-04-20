#pragma once

#include "Events/Event.h"

namespace Boreal {

	class Application {
	public:
		Application();
		virtual ~Application();

		bool Init();

		void Run();

		void Shutdown();
	};

}
