#include "bopch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Boreal {

	Application::Application()
	{}

	Application::~Application()
	{}

	bool Application::Init()
	{
		return true;
	}

	void Application::Run()
	{

		while (m_Running) 
		{
			// TEMP ====================
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
			//==========================
		}
	}

	void Application::OnEvent(Event& e)
	{}

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

}