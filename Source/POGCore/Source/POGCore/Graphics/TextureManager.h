#pragma once

#include "POGGraphics.h"

namespace POG::Core
{
	class TextureManager
	{
	public:
		static void Init();

		static Graphics::Texture& CreateGlobalTexture(const char* name) { return globalTextureManager->CreateTexture(name); }
		static void DestroyGlobalTexture(const char* name) { globalTextureManager->DestroyTexture(name); }

		static Graphics::Texture& GetGlobalTexture(const char* name) { return globalTextureManager->GetTexture(name); }

		TextureManager();

		virtual ~TextureManager();

		Graphics::Texture& CreateTexture(const char* name);
		void DestroyTexture(const char* name);

		Graphics::Texture& GetTexture(const char* name) { return *textures[name]; }

	private:
		static std::unique_ptr<TextureManager> globalTextureManager;

		std::map<const char*, Graphics::Texture*> textures;
	};
}

