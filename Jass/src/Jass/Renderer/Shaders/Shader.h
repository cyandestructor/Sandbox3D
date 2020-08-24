#ifndef JASS_SHADER_H
#define JASS_SHADER_H

#include "Jass/Core/Core.h"
#include "Jass/JMath/JMath.h"

#include <string>

namespace Jass {

	class JASS_API Shader {

	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat3(const std::string& name, const JVec3& vector) = 0;
		virtual void SetFloat4(const std::string& name, const JVec4& vector) = 0;
		virtual void SetMat4(const std::string& name, const JMat4& vector) = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);

	};

}

#endif // !JASS_SHADER_H
