#include "bopch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Utility/Time.h"
#include "Log.h"
#include "Platform/Windows/WindowsInput.h"

#include "KeyCodes.h"

namespace Boreal {

	Application* Application::s_Instance = nullptr;
	Input* Input::s_Instance = new WindowsInput();

	Application::Application()
	{
		s_Instance = this;

		m_Window = Ref<Window>(Window::Create());
		m_Window->SetEventCallback(BOREAL_BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{}

	bool Application::Init()
	{
		return true;
	}

	void Application::Run()
	{
		// Timestep frame time
		float lastFrameTime = Time::GetTime();

		while (m_Running) 
		{
			// Timestep
			float currentTime = Time::GetTime();
			Timestep ts = currentTime - lastFrameTime;
			lastFrameTime = currentTime;

			// Test
			if (Input::IsKeyPressed(87))
				BO_ERROR("W Key is being pressed!");

			// Update layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(ts);

			// Update window
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		// Dispatch specific events
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BOREAL_BIND_EVENT_FN(OnWindowClose));

		// Forward events to layers (if needed)
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::Shutdown()
	{}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}