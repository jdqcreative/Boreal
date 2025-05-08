#pragma once

#include "Boreal/Base.h"
#include "../vendor/alder/alder.h"

namespace Boreal {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Setmat4(const std::string& name, const alder::mat4& value) = 0;
		virtual void SetFloat4(const std::string& name, const alder::vec4& value) = 0;
		virtual void SetInt(const std::string& name, int value) = 0;

		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}