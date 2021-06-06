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

	FrameBuffer::~FrameBuffer()
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