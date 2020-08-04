#ifndef JASS_SHADER_H
#define JASS_SHADER_H

#include "jasspch.h"
#include <glm/glm.hpp>

namespace Jass {

	class JASS_API Shader {

	public:
		Shader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
		virtual ~Shader();

		void Bind();
		void Unbind();

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		unsigned int m_program = 0;

	};

}

#endif // !JASS_SHADER_H
