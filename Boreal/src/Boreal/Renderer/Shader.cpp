#include "bopch.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Boreal/Base.h"

namespace Boreal {

	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc);
	}

}