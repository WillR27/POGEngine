#pragma once

#include "Shader.h"

namespace PEngine
{
	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();

		Shared<Shader> FindShader(std::string name);
		Shared<Shader> CreateShader();
		Shared<Shader> CreateAndAddShader(std::string name);
		void AddShader(std::string name, Shared<Shader> shader);

	private:
		std::unordered_map<std::string, Shared<Shader>> shaders;
	};
}

