#include "pgepch.h"
#include "ShaderManager.h"

namespace PEngine
{
	ShaderManager::ShaderManager()
	{
	}

	ShaderManager::~ShaderManager()
	{
	}

	Shared<Shader> ShaderManager::FindShader(std::string name)
	{
		try
		{
			return shaders.at(name);
		}
		catch (std::exception ex)
		{
			PG_WARN("Shader \"{0}\" does not exist!", name);
			return Shared<Shader>(nullptr);
		}
	}

	Shared<Shader> ShaderManager::CreateShader()
	{
		return MakeShared<Shader>();
	}

	Shared<Shader> ShaderManager::CreateAndAddShader(std::string name)
	{
		Shared<Shader> shader = CreateShader();

		AddShader(name, shader);

		return shader;
	}

	void ShaderManager::AddShader(std::string name, Shared<Shader> shader)
	{
		try
		{
			// Check the shader doesn't already exist
			// If it does, warn the user that it is being replaced
			Shared<Shader> shader = shaders.at(name);
			PG_WARN("Replacing shader \"{0}\"!", name);
		}
		catch (std::exception ex)
		{
		}

		// Either way set the shader
		shaders[name] = shader;
	}
}
