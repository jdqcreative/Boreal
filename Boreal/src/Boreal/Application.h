#pragma once

#include "Events/Event.h"
#include "Boreal/Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Boreal/Window.h"

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

		// Event handlers
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
	};

}

#define BOREAL_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }