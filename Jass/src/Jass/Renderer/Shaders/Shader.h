#ifndef JASS_SHADER_H
#define JASS_SHADER_H

#include "Jass/Core.h"
#include <string>

namespace Jass {

	class JASS_API Shader {

	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);

	};

}

#endif // !JASS_SHADER_H
