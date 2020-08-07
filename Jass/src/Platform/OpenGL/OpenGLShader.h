#ifndef OPENGL_SHADER_H_JASS
#define OPENGL_SHADER_H_JASS

#include "Jass/Renderer/Shader.h"

namespace Jass {

	class JASS_API OpenGLShader : public Shader {

	public:
		OpenGLShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
		virtual ~OpenGLShader();

		virtual void Bind() override;
		virtual void Unbind() override;

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformInt2(const std::string& name, const glm::vec2& values);
		void UploadUniformInt3(const std::string& name, const glm::vec3& values);
		void UploadUniformInt4(const std::string& name, const glm::vec4& values);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		unsigned int m_rendererID = 0;

	};

}

#endif // !OPENGL_SHADER_H_JASS
