#include "jasspch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Jass {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				JASS_CORE_ASSERT(false, "Renderer API None is currently not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return MakeRef<OpenGLVertexArray>();
		}

		JASS_CORE_ASSERT(false, "Unknow Renderer API");
		return nullptr;
	}

}

