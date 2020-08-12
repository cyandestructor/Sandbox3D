#include "jasspch.h"

#include "ShaderLibrary.h"

namespace Jass {

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		const auto& name = shader->GetName();
		JASS_CORE_ASSERT(!Exists(name), "The shader already exists");
		m_shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		JASS_CORE_ASSERT(!Exists(name), "The shader already exists");
		m_shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(name, filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader>& ShaderLibrary::GetShader(const std::string& name)
	{
		JASS_CORE_ASSERT(Exists(name), "The shader was not found");
		return m_shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_shaders.find(name) != m_shaders.end();
	}

}