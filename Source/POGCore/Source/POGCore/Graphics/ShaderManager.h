#pragma once

#include "POGGraphics.h"

namespace POG::Core
{
	class ShaderManager
	{
	public:
		static void Init();

		static Graphics::Shader& CreateGlobalShader(const char* name) { return globalShaderManager->CreateShader(name); }
		static void DestroyGlobalShader(const char* name) { globalShaderManager->DestroyShader(name); }

		static Graphics::Shader& GetGlobalShader(const char* name) { return globalShaderManager->GetShader(name); }

		static Graphics::Shader& GetDefaultShader(const char* name) { return defaultShaderManager->GetShader(name); }

		ShaderManager();

		virtual ~ShaderManager();

		Graphics::Shader& CreateShader(const char* name);
		void DestroyShader(const char* name);

		Graphics::Shader& GetShader(const char* name) { return *shaders[name]; }

	private:
		static std::unique_ptr<ShaderManager> globalShaderManager;
		static std::unique_ptr<ShaderManager> defaultShaderManager;

		std::map<const char*, Graphics::Shader*> shaders;
	};
}

