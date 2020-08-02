#include "jasspch.h"
#include "RendererAPI.h"

namespace Jass {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	RendererAPI::API RendererAPI::GetAPI()
	{
		return s_API;
	}

}