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
		// TEMP ====================
		WindowResizeEvent e(1200, 720);
		Event& base = e;

		EventDispatcher dispatcher(base);
		dispatcher.Dispatch<WindowResizeEvent>([](WindowResizeEvent& e) {
			std::cout << "Window Width: " << e.GetWidth() << std::endl;
			return true;
			});

		BO_INFO(e.ToString());
		//==========================

		while (true) {}
	}

	void Application::Shutdown()
	{}

}