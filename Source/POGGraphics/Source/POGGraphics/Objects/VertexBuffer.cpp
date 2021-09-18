#include "POGGraphicsPCH.h"
#include "VertexBuffer.h"

#include <glad/glad.h>

namespace POG::Graphics
{
	VertexBuffer* VertexBuffer::currentVBO = nullptr;

	VertexBuffer::VertexBuffer()
		: RenderingObject::RenderingObject()
	{
		glGenBuffers(1, &id);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
		currentVBO = this;
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	RenderingObject* VertexBuffer::GetCurrent()
	{
		return currentVBO;
	}

	void VertexBuffer::SetVertexData(const void* vertexData, unsigned int size)
	{
		glBufferData(GL_ARRAY_BUFFER, size, vertexData, GL_STATIC_DRAW);
	}
}