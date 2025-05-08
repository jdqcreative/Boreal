#pragma once

//#include "../vendor/alder/alder.h"

#include "RendererAPI.h"

namespace Boreal {

	class RenderCommand
	{
	public:
		static void Init();
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void SetClearColor(const alder::vec4& color);
		static void Clear();
		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0);

	private:
		static Scope<RendererAPI> s_RendererAPI;
	};

}