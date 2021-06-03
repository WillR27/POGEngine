#pragma once

#include "POGRender.h"

namespace POG::Core
{
	class TextureManager
	{
	public:
		static void Init();

		static Render::Texture& CreateGlobalTexture(const char* name) { return globalTextureManager->CreateTexture(name); }
		static void DestroyGlobalTexture(const char* name) { globalTextureManager->DestroyTexture(name); }

		static Render::Texture& GetGlobalTexture(const char* name) { return globalTextureManager->GetTexture(name); }

		TextureManager();

		virtual ~TextureManager();

		Render::Texture& CreateTexture(const char* name);
		void DestroyTexture(const char* name);

		Render::Texture& GetTexture(const char* name) { return *textures[name]; }

	private:
		static std::unique_ptr<TextureManager> globalTextureManager;

		std::map<const char*, Render::Texture*> textures;
	};
}

