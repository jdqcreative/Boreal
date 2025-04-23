#include <Boreal.h>

class ExampleLayer : public Boreal::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate(Boreal::Timestep ts) override
	{
		BO_INFO("Delta Time: {}", ts.GetMilliseconds());
	}

	void OnEvent(Boreal::Event& event) override
	{
		BO_WARN("{}", event.ToString());
	}
};

class ExampleApp : public Boreal::Application
{
public:
	ExampleApp() 
	{
		PushLayer(new ExampleLayer());
	}

	~ExampleApp() {}

};

Boreal::Application* CreateApplication() {
	return new ExampleApp();
}