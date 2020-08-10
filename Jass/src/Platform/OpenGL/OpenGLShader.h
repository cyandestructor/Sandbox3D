#ifndef OPENGL_SHADER_H_JASS
#define OPENGL_SHADER_H_JASS

#include "Jass/Renderer/Shader.h"
#include "Jass/JMath/JMath.h"

#include <unordered_map>

namespace Jass {

	class JASS_API OpenGLShader : public Shader {

	public:
		OpenGLShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
		virtual ~OpenGLShader();

		virtual void Bind() override;
		virtual void Unbind() override;

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformInt2(const std::string& name, const JVec2& values);
		void UploadUniformInt3(const std::string& name, const JVec3& values);
		void UploadUniformInt4(const std::string& name, const JVec4& values);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const JVec2& values);
		void UploadUniformFloat3(const std::string& name, const JVec3& values);
		void UploadUniformFloat4(const std::string& name, const JVec4& values);
		void UploadUniformMat3(const std::string& name, const JMat3& matrix);
		void UploadUniformMat4(const std::string& name, const JMat4& matrix);

	private:
		unsigned int m_rendererID = 0;
		std::unordered_map<std::string, int> m_uniformLocationCache;

		enum class ShaderType {
			VertexShader, FragmentShader
		};

		static unsigned int ToGLenum(ShaderType type);
		unsigned int CompileShader(const std::string& src, ShaderType type);
		unsigned int CreateAndLinkProgram(unsigned int vertexShader, unsigned int fragmentShader);

		int GetUniformLocation(const std::string& name);

	};

}

#endif // !OPENGL_SHADER_H_JASS
