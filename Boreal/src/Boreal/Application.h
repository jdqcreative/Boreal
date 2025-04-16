#pragma once

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
