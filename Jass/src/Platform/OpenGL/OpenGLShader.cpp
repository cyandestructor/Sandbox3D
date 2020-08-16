#include "jasspch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <fstream>
#include <filesystem>

namespace Jass {

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string fullSource = ReadFile(filepath);
		auto sources = Preprocess(fullSource);
		CompileProgram(sources);

		//Get the name from the filepath
		std::filesystem::path shaderPath(filepath);
		JASS_CORE_ASSERT(shaderPath.has_stem(), "The filepath is not valid");
		m_name = shaderPath.stem().string();
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& filepath) :
		m_name(name)
	{
		std::string fullSource = ReadFile(filepath);
		auto sources = Preprocess(fullSource);
		CompileProgram(sources);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc) :
		m_name(name)
	{
		std::unordered_map<unsigned int, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexShaderSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentShaderSrc;

		CompileProgram(sources);
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

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string source;

		std::ifstream file(filepath, std::ios::in | std::ios::binary);

		if (file) {
			file.seekg(0, std::ios::end);
			// Resize the string to the size of the file
			source.resize(file.tellg());
			file.seekg(0, std::ios::beg);
			file.read(&source[0], source.size());

			file.close();
		}
		else {
			JASS_CORE_ERR("Could not open the file: {0}", filepath);
		}

		return source;
	}

	unsigned int OpenGLShader::ToGLenum(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		else if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		JASS_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}

	std::unordered_map<unsigned int, std::string> OpenGLShader::Preprocess(const std::string& source)
	{
		std::unordered_map<unsigned int /*type*/, std::string /*source*/> sources;

		// Define the toke and its length
		const char token[] = "#type";
		size_t tokenSize = strlen(token);

		size_t tokenPos = source.find(token);
		while (tokenPos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", tokenPos);
			JASS_CORE_ASSERT(eol != std::string::npos, "Syntax error");

			// Get the type of the shader
			size_t begin = tokenPos + tokenSize + 1;
			std::string type = source.substr(begin, eol - begin);
			JASS_CORE_ASSERT(ToGLenum(type), "Syntax error");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			// Find if there is another shader type
			tokenPos = source.find(token, nextLinePos);
			size_t srcEnd = nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos;

			// Get and save the source of the shader
			sources[ToGLenum(type)] = source.substr(nextLinePos, tokenPos - srcEnd);
		}

		return sources;
	}

	unsigned int OpenGLShader::CompileShader(const std::string& src, unsigned int type)
	{
		// Create an empty shader handle.
		unsigned int shader = glCreateShader(type);

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

	unsigned int OpenGLShader::CreateAndLinkProgram(const std::vector<unsigned int>& shaders)
	{
		// Get a program object.
		unsigned int program = glCreateProgram();

		// Attach our shaders to our program.
		for (auto shader : shaders)
			glAttachShader(program, shader);

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
			for (auto shader : shaders)
				glDeleteShader(shader);

			JASS_CORE_ERR("{0}", infoLog.data());
			JASS_CORE_ASSERT(false, "Program linking error");

			return 0;
		}

		// Always detach shaders after a successful link.
		for (auto shader : shaders)
			glDetachShader(program, shader);

		// Return the program object when the link is successful.
		return program;
	}

	void OpenGLShader::CompileProgram(const std::unordered_map<unsigned int, std::string>& sources)
	{
		std::vector<unsigned int> shaders;
		shaders.reserve(sources.size());

		for (const auto& shader : sources)
		{
			unsigned int type = shader.first;
			const std::string& source = shader.second;

			shaders.push_back(CompileShader(source, type));
		}

		JASS_CORE_ASSERT(shaders.size(), "There are no compiled shaders");

		m_rendererID = CreateAndLinkProgram(shaders);
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