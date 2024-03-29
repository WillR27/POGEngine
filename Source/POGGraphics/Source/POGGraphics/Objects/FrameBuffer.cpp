#include "POGGraphicsPCH.h"
#include "FrameBuffer.h"

#include <glad/glad.h>

namespace POG::Graphics
{
	FrameBuffer* FrameBuffer::currentFBO = nullptr;

	FrameBuffer::FrameBuffer()
		: RenderingObject::RenderingObject()
	{
		glGenFramebuffers(1, &id);
	}

	FrameBuffer::FrameBuffer(const FrameBuffer& frameBuffer)
		: RenderingObject::RenderingObject(frameBuffer)
	{
	}

	FrameBuffer::~FrameBuffer()
	{
		if (GetRefCount() == 1)
		{
			Dispose();
		}
	}

	FrameBuffer& FrameBuffer::operator=(const FrameBuffer& frameBuffer)
	{
		RenderingObject::operator=(frameBuffer);

		return *this;
	}

	void FrameBuffer::Dispose()
	{
		glDeleteFramebuffers(1, &id);
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, id);
		currentFBO = this;
	}

	void FrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::BindTexture(const Texture& texture)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	}

	RenderingObject* FrameBuffer::GetCurrent()
	{
		return currentFBO;
	}
}