#include <Boreal.h>
//#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Boreal::Layer
{
public:
	ExampleLayer()
		: Layer("Example") 
	{
		// Position (x, y, z), Color (r, g, b, a)
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f
		};

		uint32_t indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		//Set viewport
		Boreal::RenderCommand::SetViewport(0, 0, 1200, 720);

		// Create vertex array and vertex buffer
		m_VertexArray = Boreal::VertexArray::Create();
		m_VertexBuffer = Boreal::VertexBuffer::Create(vertices, sizeof(vertices));

		// Set layout
		Boreal::BufferLayout layout = {
			{ Boreal::ShaderDataType::Float3, "a_Position"},
			{ Boreal::ShaderDataType::Float4, "a_Color"}
		};
		m_VertexBuffer->SetLayout(layout);

		// Attach to vertex array
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		// Create index buffer
		m_IndexBuffer = Boreal::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		// Attach index buffer
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		// Create shader
		const std::string vertexSrc = R"(
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec4 v_Color;

void main()
{
	v_Color = a_Color;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}
)";

		const std::string fragmentSrc = R"(
#version 330 core
in vec4 v_Color;
out vec4 color;

void main()
{
	color = v_Color;
}
)";

		m_Shader = Boreal::Shader::Create(vertexSrc, fragmentSrc);
		m_CameraController = Boreal::OrthographicCameraController(Boreal::Application::Get().GetWindow().GetWidth() / Boreal::Application::Get().GetWindow().GetHeight());
	}

	void OnUpdate(Boreal::Timestep ts) override
	{
		// Clear screen
		Boreal::RenderCommand::SetClearColor(alder::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Boreal::RenderCommand::Clear();

		// Submit draw
		m_CameraController.OnUpdate(ts);

		Boreal::Renderer2D::Init();
		Boreal::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Boreal::Renderer2D::DrawQuad({ 1.0f, 1.0f }, { 0.5f, 0.5f }, {1.0f, 0.0f, 0.0f, 1.0f});
		Boreal::Renderer2D::EndScene();
	}

	void OnEvent(Boreal::Event& event) override
	{
		BO_WARN("{}", event.ToString());
	}

private:
	std::shared_ptr<Boreal::VertexArray> m_VertexArray;
	std::shared_ptr<Boreal::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Boreal::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Boreal::Shader> m_Shader;
	Boreal::OrthographicCameraController m_CameraController;

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