#include "bopch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Boreal {

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		Compile(vertexSrc, fragmentSrc);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	// Set uniform functions
	void OpenGLShader::Setmat4(const std::string& name, const alder::mat4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, alder::value_ptr(value));
	}

	void OpenGLShader::SetFloat4(const std::string& name, const alder::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	// Compile shader
	void OpenGLShader::Compile(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// Create an empty vertex shader handle
		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infolog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infolog[0]);

			glDeleteShader(vertexShader);

			std::cerr << "Vertex shader compilation error: " << infolog.data() << std::endl;
			return;
		}

		// Create an empty fragment shader handle
		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infolog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infolog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			std::cerr << "Fragment shader compilation error: " << infolog.data() << std::endl;
			return;
		}

		// Create shader program
		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infolog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infolog[0]);

			glDeleteProgram(m_RendererID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			std::cerr << "Shader linking errer: " << infolog.data() << std::endl;
			return;
		}

		// Cleanup shaders (no longer needed after linking)
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
}