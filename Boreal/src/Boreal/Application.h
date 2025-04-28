#pragma once

#include "Base.h"
#include "Events/Event.h"
#include "Boreal/Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Boreal/Window.h"

namespace Boreal {

	class Application {
	public:
		static Application& Get() { return *s_Instance; }

		Application();
		virtual ~Application();

		bool Init();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Shutdown();

		Window& GetWindow() { return *m_Window; }

		// Event handlers
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		static Application* s_Instance;
		Ref<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
	};

}

#define BOREAL_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }