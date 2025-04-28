#include <Boreal.h>
//#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Boreal::Layer
{
public:
	ExampleLayer()
		: Layer("Example") 
	{
		float vertices[6] = {
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0.0f, 0.5f
		};

		uint32_t indices[3] = {
			0, 1, 2
		};

		//Set viewport
		Boreal::RenderCommand::SetViewport(0, 0, 1280, 720);

		// Create vertex array and vertex buffer
		m_VertexArray = Boreal::VertexArray::Create();
		m_VertexBuffer = Boreal::VertexBuffer::Create(vertices, sizeof(vertices));

		// Set layout
		Boreal::BufferLayout layout = {
			{ Boreal::ShaderDataType::Float2, "a_Position"}
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
layout(location = 0) in vec2 a_Position;

void main()
{
	gl_Position = vec4(a_Position, 0.0, 1.0);
}
)";

		const std::string fragmentSrc = R"(
#version 330 core
out vec4 color;

void main()
{
	color = vec4(0.8, 0.3, 0.2, 1.0);
}
)";

		m_Shader = Boreal::Shader::Create(vertexSrc, fragmentSrc);
	}

	void OnUpdate(Boreal::Timestep ts) override
	{
		// Clear screen
		Boreal::RenderCommand::SetClearColor(alder::Vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Boreal::RenderCommand::Clear();

		// Bind shader and VAO
		m_Shader->Bind();
		m_VertexArray->Bind();

		// Submit draw
		Boreal::RenderCommand::DrawIndexed(m_VertexArray);
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