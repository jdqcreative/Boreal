#include "bopch.h"
#include "UI.h"

namespace ColdSnap {

	void Init()
	{
		// Init stuff (load fonts, etc.)
	}

	void Shutdown()
	{
		g_Context.DrawList.clear();
	}

	void NewFrame(const InputState& input)
	{
		g_Context.Input = input;
		g_Context.DrawList.clear();
		g_Context.CursorPos = { 10, 10 }; // reset layout start
	}

	void Render()
	{
		// Render logic
	}

	bool Button(const char* label)
	{
		Vec2 pos = g_Context.CursorPos;
		Vec2 size = { 100, 30 };

		bool hovered = (g_Context.Input.MousePos.x >= pos.x && g_Context.Input.MousePos.x <= pos.x + size.x &&
						g_Context.Input.MousePos.y >= pos.y && g_Context.Input.MousePos.y <= pos.y + size.y);

		bool clicked = hovered && g_Context.Input.MouseDown[0];

		// Add the button to the draw list
		g_Context.DrawList.push_back(
			{
				pos, size,
				hovered ? Color{0.8f, 0.8f, 0.9f, 1.0f} : Color{0.6f, 0.6f, 0.6f, 1.0f},
				label
			}
		);

		return clicked;
	}
}