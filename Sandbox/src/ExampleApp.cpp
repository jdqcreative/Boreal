#include <Boreal.h>

class ExampleApp : public Boreal::Application
{
public:
	ExampleApp() {}
	~ExampleApp() {}

};

Boreal::Application* CreateApplication() {
	return new ExampleApp();
}