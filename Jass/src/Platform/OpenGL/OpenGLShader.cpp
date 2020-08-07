#include "jasspch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Jass {

	OpenGLShader::OpenGLShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
	{
		// Create an empty vertex shader handle
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const char* source = vertexShaderSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		int isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			JASS_CORE_ERR("{0}", infoLog.data());
			JASS_CORE_ASSERT(false, "Vertex shader compilation error");

			return;
		}

		// Create an empty fragment shader handle
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentShaderSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			JASS_CORE_ERR("{0}", infoLog.data());
			JASS_CORE_ASSERT(false, "Fragment shader compilation error");

			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_rendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_rendererID, vertexShader);
		glAttachShader(m_rendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_rendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		int isLinked = 0;
		glGetProgramiv(m_rendererID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_rendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_rendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			JASS_CORE_ERR("{0}", infoLog.data());
			JASS_CORE_ASSERT(false, "Program linking error");

			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_rendererID, vertexShader);
		glDetachShader(m_rendererID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(0);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_rendererID);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		auto location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformInt2(const std::string& name, const glm::vec2& values)
	{
		auto location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform2i(location, (int)values.x, (int)values.y);
	}

	void OpenGLShader::UploadUniformInt3(const std::string& name, const glm::vec3& values)
	{
		auto location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform3i(location, (int)values.x, (int)values.y, (int)values.z);
	}

	void OpenGLShader::UploadUniformInt4(const std::string& name, const glm::vec4& values)
	{
		auto location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform4i(location, (int)values.x, (int)values.y, (int)values.z, (int)values.w);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		auto location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		auto location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		auto location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		auto location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		auto location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		auto location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}