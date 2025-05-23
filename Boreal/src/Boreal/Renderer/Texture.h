#pragma once

#include <string>
#include <cstdint>

#include "Boreal/Base.h"

namespace Boreal {

	class Texture2D
	{
	public:
		virtual ~Texture2D() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

		static Ref<Texture2D> Create(const std::string& path);
	};

}