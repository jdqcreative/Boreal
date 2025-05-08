#include "bopch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Boreal {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = []() -> Scope<RendererAPI> {
		switch (RendererAPI::GetAPI())
		{
		case RendererAPIType::OpenGL: return CreateScope<OpenGLRendererAPI>(OpenGLRendererAPI());
		case RendererAPIType::Vulkan: return nullptr;
		case RendererAPIType::DirectX: return nullptr;
		case RendererAPIType::None: return nullptr;
		}
		return nullptr;
	}();

	void RenderCommand::Init() 
	{ 
		s_RendererAPI->Init(); 
	}

	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		s_RendererAPI->SetViewport(x, y, width, height);
	}

	void RenderCommand::SetClearColor(const alder::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		s_RendererAPI->DrawIndexed(vertexArray, indexCount);
	}
}





