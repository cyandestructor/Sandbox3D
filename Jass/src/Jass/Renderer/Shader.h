#ifndef JASS_SHADER_H
#define JASS_SHADER_H

#include <string>

namespace Jass {

	class JASS_API Shader {

	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);

	};

}

#endif // !JASS_SHADER_H
