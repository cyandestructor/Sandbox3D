#include "jasspch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Jass {

	OpenGLShader::OpenGLShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
	{
		// Compile a vertex shader and get its handle
		unsigned int vertexShader = CompileShader(vertexShaderSrc, ShaderType::VertexShader);
		// Compile a fragment shader and get its handle
		unsigned int fragmentShader = CompileShader(fragmentShaderSrc, ShaderType::FragmentShader);

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		m_rendererID = CreateAndLinkProgram(vertexShader, fragmentShader);
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
		int location = GetUniformLocation(name);
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformInt2(const std::string& name, const JVec2& values)
	{
		int location = GetUniformLocation(name);
		glUniform2i(location, (int)values.x, (int)values.y);
	}

	void OpenGLShader::UploadUniformInt3(const std::string& name, const JVec3& values)
	{
		int location = GetUniformLocation(name);
		glUniform3i(location, (int)values.x, (int)values.y, (int)values.z);
	}

	void OpenGLShader::UploadUniformInt4(const std::string& name, const JVec4& values)
	{
		int location = GetUniformLocation(name);
		glUniform4i(location, (int)values.x, (int)values.y, (int)values.z, (int)values.w);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		int location = GetUniformLocation(name);
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const JVec2& values)
	{
		int location = GetUniformLocation(name);
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const JVec3& values)
	{
		int location = GetUniformLocation(name);
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const JVec4& values)
	{
		int location = GetUniformLocation(name);
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const JMat3& matrix)
	{
		int location = GetUniformLocation(name);
		glUniformMatrix3fv(location, 1, GL_FALSE, GetPtr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const JMat4& matrix)
	{
		int location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, GetPtr(matrix));
	}

	unsigned int OpenGLShader::ToGLenum(ShaderType type)
	{
		switch (type)
		{
			case OpenGLShader::ShaderType::VertexShader:
				return GL_VERTEX_SHADER;
			case OpenGLShader::ShaderType::FragmentShader:
				return GL_FRAGMENT_SHADER;
		}

		JASS_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}

	unsigned int OpenGLShader::CompileShader(const std::string& src, ShaderType type)
	{
		// Create an empty shader handle.
		unsigned int shader = glCreateShader(ToGLenum(type));

		// Send the shader source code to GL.
		// Note that std::string's .c_str is NULL character terminated.
		const char* source = src.c_str();
		glShaderSource(shader, 1, &source, 0);

		// Compile the shader.
		glCompileShader(shader);

		int isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character.
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(shader);

			JASS_CORE_ERR("{0}", infoLog.data());
			JASS_CORE_ASSERT(false, "Shader compilation error");

			return 0;
		}

		// Return the shader handle if the compilation is successful.
		return shader;
	}

	unsigned int OpenGLShader::CreateAndLinkProgram(unsigned int vertexShader, unsigned int fragmentShader)
	{
		// Get a program object.
		unsigned int program = glCreateProgram();

		// Attach our shaders to our program.
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program.
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		int isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character.
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			JASS_CORE_ERR("{0}", infoLog.data());
			JASS_CORE_ASSERT(false, "Program linking error");

			return 0;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);

		// Return the program object when the link is successful.
		return program;
	}

	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];

		int location = glGetUniformLocation(m_rendererID, name.c_str());
		if (location == -1)
			JASS_CORE_WARN("{0} uniform was not found", name);

		m_uniformLocationCache[name] = location;

		return location;
	}

}