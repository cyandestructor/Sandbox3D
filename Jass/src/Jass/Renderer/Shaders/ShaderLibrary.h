#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include "Shader.h"

namespace Jass {

	class JASS_API ShaderLibrary {

	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);

		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		Ref<Shader> Load(const std::string& filepath);

		Ref<Shader>& GetShader(const std::string& name);

		bool Exists(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_shaders;

	};

}

#endif // !SHADER_LIBRARY_H
