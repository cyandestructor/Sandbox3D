#include "jasspch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Jass {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			JASS_CORE_ASSERT(false, "Renderer API None is currently not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}

		JASS_CORE_ASSERT(false, "Unknow Renderer API");
		return nullptr;
	}

}

