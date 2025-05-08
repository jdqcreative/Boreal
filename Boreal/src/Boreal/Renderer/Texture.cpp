#include "bopch.h"
#include "Texture.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Boreal {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		return CreateRef<OpenGLTexture2D>(path);
	}

}