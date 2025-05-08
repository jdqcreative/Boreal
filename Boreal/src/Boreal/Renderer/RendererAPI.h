#pragma once

#include "bopch.h"

//#include "../vendor/alder/alder.h"
#include "Boreal/Base.h"
#include "Boreal/Renderer/VertexArray.h"
#include "Boreal/Renderer/Shader.h"

namespace Boreal {

	enum class RendererAPIType
	{
		None = 0,
		OpenGL,
		Vulkan,
		DirectX,
	};

	class RendererAPI
	{
	public:
		RendererAPI() = default;
		~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const alder::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		static RendererAPIType GetAPI() { return s_API; }

	protected:
		static RendererAPIType s_API;
	};

}