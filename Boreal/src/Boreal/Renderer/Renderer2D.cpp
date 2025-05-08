#include "bopch.h"
#include "Renderer2D.h"

namespace Boreal {

	const uint32_t MaxQuads = 10000;
	const uint32_t MaxVertices = MaxQuads * 4;
	const uint32_t MaxIndices = MaxQuads * 6;
	const uint32_t MaxTextureSlots = 16;

	struct QuadVertex
	{
		alder::vec3 Position;
		alder::vec4 Color;
		alder::vec2 TexCoord;
		float TexIndex;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> QuadShader;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		alder::vec4 QuadVertexPositions[4];
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex"}
			});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		// Create and upload index buffer
		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		// TODO: load default texture and shader, etc.

		// Store static quad corner positions
		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };

		// Default shader code
		const std::string vertexSrc = 
			R"(
				#version 330 core
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;
				layout(location = 2) in vec2 a_TexCoord;
				layout(location = 3) in float a_TexIndex;

				uniform mat4 u_ViewProjection;

				out vec4 v_Color;
				out vec2 v_TexCoord;
				out float v_TexIndex;

				void main()
				{
					v_Color = a_Color;
					v_TexCoord = a_TexCoord;
					v_TexIndex = a_TexIndex;
					gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
				}
			)";

		const std::string fragmentSrc =
			R"(
				#version 330 core

				in vec4 v_Color;
				in vec2 v_TexCoord;
				in float v_TexIndex;

				out vec4 FragColor;

				void main()
				{
					FragColor = v_Color;
				}
			)";

		s_Data.QuadShader = Shader::Create(vertexSrc, fragmentSrc);
	}

	void Renderer2D::Shutdown()
	{
		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::BeginScene(const Camera& camera)
	{
		s_Data.QuadShader->Bind();
		s_Data.QuadShader->Setmat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{
		// Ensure shader is bound (it should be already from BeginScene())
		s_Data.QuadShader->Bind();

		// Upload data to GPU
		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		// Draw call
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const alder::vec2& position, const alder::vec2& size, const alder::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const alder::vec3& position, const alder::vec2& size, const alder::vec4& color)
	{
		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushandReset();

		alder::mat4 transform = alder::translate(alder::mat4(1.0f), position)
			* alder::scale(alder::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < 4; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = GetDefaultTexCoord(i);
			s_Data.QuadVertexBufferPtr->TexIndex = 0.0f; // White texture
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;
	}

	alder::vec2 Renderer2D::GetDefaultTexCoord(int index)
	{
		switch (index)
		{
		case 0: return { 0.0f, 0.0f };
		case 1: return { 1.0f, 0.0f };
		case 2: return { 1.0f, 1.0f };
		case 3: return { 0.0f, 1.0f };
		}
		return { 0.0f, 0.0f };
	}

	void Renderer2D::FlushandReset()
	{
		EndScene();
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}
}