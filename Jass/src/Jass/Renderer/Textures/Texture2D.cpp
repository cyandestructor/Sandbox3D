#include "jasspch.h"
#include "Texture2D.h"

#include "Jass/Renderer/Renderer.h"
#include "Platform/OpenGL/Textures/OpenGLTexture2D.h"

namespace Jass {

	Ref<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				JASS_CORE_ASSERT(false, "Renderer API None is currently not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLTexture2D>(filepath);
		}

		JASS_CORE_ASSERT(false, "Unknow Renderer API");
		return nullptr;
	}

}
