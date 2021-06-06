#pragma once

#include "POGRender.h"

namespace POG::Core
{
	class ShaderManager
	{
	public:
		static void Init();

		static Render::Shader& CreateGlobalShader(const char* name) { return globalShaderManager->CreateShader(name); }
		static void DestroyGlobalShader(const char* name) { globalShaderManager->DestroyShader(name); }

		static Render::Shader& GetGlobalShader(const char* name) { return globalShaderManager->GetShader(name); }

		static Render::Shader& GetDefaultShader(const char* name) { return defaultShaderManager->GetShader(name); }

		ShaderManager();

		virtual ~ShaderManager();

		Render::Shader& CreateShader(const char* name);
		void DestroyShader(const char* name);

		Render::Shader& GetShader(const char* name) { return *shaders[name]; }

	private:
		static std::unique_ptr<ShaderManager> globalShaderManager;
		static std::unique_ptr<ShaderManager> defaultShaderManager;

		std::map<const char*, Render::Shader*> shaders;
	};
}
