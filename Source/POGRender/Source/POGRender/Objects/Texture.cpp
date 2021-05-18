#include "POGRenderPCH.h"
#include "Texture.h"

#include <glad/glad.h>

namespace POG::Render
{
	Texture* Texture::currentFBO = nullptr;

	Texture::Texture()
		: RenderingObject::RenderingObject()
	{
		glGenTextures(1, &id);

		// TODO: Not this lol
		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1000, 800, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &id);
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, id);
		currentFBO = this;
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	RenderingObject* Texture::GetCurrent()
	{
		return currentFBO;
	}
}