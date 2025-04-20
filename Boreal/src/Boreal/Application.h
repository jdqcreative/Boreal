#pragma once

#include "Events/Event.h"
#include "LayerStack.h"

namespace Boreal {



	class Application {
	public:
		Application();
		virtual ~Application();

		bool Init();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Shutdown();

	private:
		LayerStack m_LayerStack;
		bool m_Running = true;
	};

}
