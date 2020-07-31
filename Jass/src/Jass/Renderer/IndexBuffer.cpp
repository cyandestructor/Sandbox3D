#include "jasspch.h"
#include "IndexBuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Jass {

	IndexBuffer* IndexBuffer::Create(const IndexBufferConfig& config)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			JASS_CORE_ASSERT(false, "Renderer API None is currently not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(config);
		}

		JASS_CORE_ASSERT(false, "Unknow Renderer API");
		return nullptr;
	}

}

