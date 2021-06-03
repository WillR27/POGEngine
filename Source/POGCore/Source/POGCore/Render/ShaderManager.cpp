#include "POGCorePCH.h"
#include "ShaderManager.h"

namespace POG::Core
{
	std::unique_ptr<ShaderManager> ShaderManager::globalShaderManager(nullptr);
	std::unique_ptr<ShaderManager> ShaderManager::defaultShaderManager(nullptr);

	void ShaderManager::Init()
	{
		globalShaderManager = std::make_unique<ShaderManager>();
		defaultShaderManager = std::make_unique<ShaderManager>();

		const char* spriteVertexShader = R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
	texCoord = aTexCoord;
}
)";

		const char* spriteFragmentShader = R"(
#version 330 core

in vec2 texCoord;

uniform sampler2D textureSample;

out vec4 FragColor;

void main()
{
	FragColor = texture(textureSample, texCoord);
} 
)";

		defaultShaderManager->CreateShader("Sprite Shader").Init(spriteVertexShader, spriteFragmentShader);;
	}

	ShaderManager::ShaderManager()
		: shaders()
	{
	}

	ShaderManager::~ShaderManager()
	{
		for (auto& pair : shaders)
		{
			delete pair.second;
		}

		shaders.clear();
	}

	Render::Shader& ShaderManager::CreateShader(const char* name)
	{
		Render::Shader* newShader = new Render::Shader();
		shaders[name] = newShader;

		return *newShader;
	}

	void ShaderManager::DestroyShader(const char* name)
	{
		if (shaders.find(name) != shaders.end())
		{
			delete shaders[name];
			shaders.erase(name);
		}
		else
		{
			POG_WARN("Tried to destroy shader \"{0}\" that didn't exist.", name);
		}
	}
}