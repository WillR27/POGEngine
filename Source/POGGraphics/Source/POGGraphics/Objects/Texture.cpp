#include "POGGraphicsPCH.h"
#include "Texture.h"

#include <glad/glad.h>

#include "POGUtil.h"

namespace POG::Graphics
{
	Texture* Texture::currentFBO = nullptr;

	Texture::Texture()
		: RenderingObject::RenderingObject()
		, width(0)
		, height(0)
	{
		glGenTextures(1, &id);

		// TODO: Not this lol
		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	Texture::Texture(const Texture& texture)
		: RenderingObject::RenderingObject(texture)
		, width(texture.width)
		, height(texture.height)
	{
	}

	Texture::~Texture()
	{
		if (GetRefCount() == 1)
		{
			Dispose();
		}
	}

	void Texture::Dispose()
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

	void Texture::SetData(void* data, int width, int height)
	{
		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		this->width = width;
		this->height = height;
	}

	void Texture::SetDataRed(void* data, int width, int height)
	{
		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		this->width = width;
		this->height = height;
	}

	void Texture::LoadFromImage(const char* file)
	{
		int width, height, channels;
		Util::Image image = Util::LoadImageFromFile(file, width, height, channels, true);
		SetData(image, width, height);
		Util::FreeImage(image);
	}

	RenderingObject* Texture::GetCurrent()
	{
		return currentFBO;
	}
}