#pragma once

#include "Boreal/Renderer/Camera.h"
#include "Boreal/Base.h"
#include "Boreal/Renderer/VertexArray.h"
#include "Boreal/Renderer/Shader.h"
#include "Boreal/Renderer/RenderCommand.h"

namespace Boreal {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void DrawQuad(const alder::vec2& position, const alder::vec2& size, const alder::vec4& color);
		static void DrawQuad(const alder::vec3& position, const alder::vec2& size, const alder::vec4& color);

	private:
		static void FlushandReset();
		static alder::vec2 GetDefaultTexCoord(int index);
	};

}