#pragma once

#include "bopch.h"

namespace Boreal {

	enum class ShaderDataType
	{
		Float, Float2, Float3, Float4,
		Mat3, mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false);
		uint32_t GetComponentCount() const;
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elements);
		uint32_t GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;

		void CalculateOffsetAndStride();
	};

}