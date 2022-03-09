#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "VertexArray.h"
#include "Orca/Core.h"

namespace Orca
{

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1

		};

	public:

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray ) = 0;

		inline static API GetAPI() { return s_Api; }

	private:
		static API s_Api;
	};

}
