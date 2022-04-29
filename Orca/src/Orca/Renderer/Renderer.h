#pragma once

#include "RenderCommand.h"

#include "Orca/Renderer/OrthographicCamera.h"
#include "Orca/Renderer/Shader.h"

namespace Orca {

	class Renderer {
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene();
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

	public:
		static Scope<Renderer::SceneData> m_SceneData;

	};


	
}