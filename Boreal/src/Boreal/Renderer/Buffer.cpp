#include "bopch.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Boreal {

	// Vertex buffer
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		return CreateRef<OpenGLVertexBuffer>(size);
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		return CreateRef<OpenGLVertexBuffer>(vertices, size);
	}

	// Index buffer
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		return CreateRef<OpenGLIndexBuffer>(indices, count);
	}
}