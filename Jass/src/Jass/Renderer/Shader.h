#ifndef JASS_SHADER_H
#define JASS_SHADER_H

#include "jasspch.h"

namespace Jass {

	class JASS_API Shader {

	public:
		Shader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
		virtual ~Shader();

		void Bind();
		void Unbind();

	private:
		unsigned int m_program = 0;

	};

}

#endif // !JASS_SHADER_H
