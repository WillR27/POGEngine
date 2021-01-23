#include "pgepch.h"
#include "IndexBuffer.h"

#include <glad/glad.h>

namespace PEngine
{
	IndexBuffer* IndexBuffer::currentIBO = nullptr;

	IndexBuffer::IndexBuffer()
		: RenderingObject::RenderingObject()
	{
		glGenBuffers(1, &id);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		currentIBO = this;
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	RenderingObject* IndexBuffer::GetCurrent()
	{
		return currentIBO;
	}

	void IndexBuffer::SetIndexData(const void* indexData, int size)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indexData, GL_STATIC_DRAW);
	}
}