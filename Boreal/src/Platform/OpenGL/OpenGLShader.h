#pragma once

#include "bopch.h"
#include "Boreal/Renderer/Shader.h"

namespace Boreal {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void Setmat4(const std::string& name, const alder::mat4& value) override;
		virtual void SetFloat4(const std::string& name, const alder::vec4& value) override;
		virtual void SetInt(const std::string& name, int value) override;

	private:
		uint32_t m_RendererID;

		void Compile(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}