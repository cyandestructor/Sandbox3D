#ifndef JASS_SHADER_H
#define JASS_SHADER_H

#include <string>
#include <glm/glm.hpp>

namespace Jass {

	class JASS_API Shader {

	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static Shader* Create(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);

	};

}

#endif // !JASS_SHADER_H
