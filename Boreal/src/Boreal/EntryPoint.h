#pragma once

extern Boreal::Application* CreateApplication();

int main(int argc, char** argv) {

	// calls user-defined application's CreateApplication function
	auto app = CreateApplication();

	// Check if Init was successful
	if (!app->Init()) {
		delete app;
		return -1;
	}

	// TEST CODE =======================
	Boreal::Log::Init();
	int count = 5;
	BO_ENGINE_WARN("Count is currently: {}", count);
	BO_INFO("Hello Boreal Engine!");
	//===================================


	// Main loop
	app->Run();

	// Clean up
	app->Shutdown();


	// Close
	delete app;
	return 0;

}