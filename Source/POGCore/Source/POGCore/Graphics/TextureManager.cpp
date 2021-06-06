#include "POGCorePCH.h"
#include "TextureManager.h"

namespace POG::Core
{
	std::unique_ptr<TextureManager> TextureManager::globalTextureManager(nullptr);

	void TextureManager::Init()
	{
		globalTextureManager = std::make_unique<TextureManager>();
	}

	TextureManager::TextureManager()
		: textures()
	{
	}

	TextureManager::~TextureManager()
	{
		for (auto& pair : textures)
		{
			delete pair.second;
		}

		textures.clear();
	}

	Graphics::Texture& TextureManager::CreateTexture(const char* name)
	{
		Graphics::Texture* newTexture = new Graphics::Texture();
		textures[name] = newTexture;

		return *newTexture;
	}

	void TextureManager::DestroyTexture(const char* name)
	{
		if (textures.find(name) != textures.end())
		{
			delete textures[name];
			textures.erase(name);
		}
		else
		{
			POG_WARN("Tried to destroy texture \"{0}\" that didn't exist.", name);
		}
	}
}