#include "bopch.h"
#include "Renderer.h"
#include "Boreal/Renderer/RenderCommand.h"
#include "Boreal/Renderer/Renderer2D.h"

namespace Boreal {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const alder::mat4 transform)
	{
		shader->Bind();
		shader->Setmat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->Setmat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}
}