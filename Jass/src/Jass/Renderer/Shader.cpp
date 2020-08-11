#include "jasspch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Jass {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				JASS_CORE_ASSERT(false, "Renderer API None is currently not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(filepath);
		}

		JASS_CORE_ASSERT(false, "Unknow Renderer API");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				JASS_CORE_ASSERT(false, "Renderer API None is currently not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(vertexShaderSrc, fragmentShaderSrc);
		}

		JASS_CORE_ASSERT(false, "Unknow Renderer API");
		return nullptr;
	}

}

