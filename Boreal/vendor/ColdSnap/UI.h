#pragma once

#include <vector>

namespace ColdSnap {

	struct Vec2
	{
		float x, y;
	};

	struct Color
	{
		float r, g, b, a;
	};

	// Allow external render backends to handle draw calls
	struct DrawCommand
	{
		Vec2 Position;
		Vec2 size;
		Color color;
		const char* label;
	};

	struct InputState
	{
		Vec2 MousePos;
		bool MouseDown[3]; // Left, right, middle
	};

	// Internal static context
	struct UIContext
	{
		std::vector<DrawCommand> DrawList;
		InputState Input;
		Vec2 CursorPos;
	};

	static UIContext g_Context;

	void Init();
	void Shutdown();

	void NewFrame(const InputState& input);
	void Render();

	bool Button(const char* label = "Button");

	const std::vector<DrawCommand>& GetDrawList() { return g_Context.DrawList; } // For rendering backend
}