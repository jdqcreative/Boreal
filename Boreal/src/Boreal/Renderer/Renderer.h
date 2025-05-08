#pragma once

#include "bopch.h"
#include "Boreal/Base.h"
#include "Boreal/Renderer/VertexArray.h"
#include "Boreal/Renderer/Camera.h"
#include "Boreal/Renderer/Shader.h"



namespace Boreal {

	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const alder::mat4 transform = alder::mat4(1.0f));

		static void Shutdown();
	private:
		struct SceneData
		{
			alder::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};

}