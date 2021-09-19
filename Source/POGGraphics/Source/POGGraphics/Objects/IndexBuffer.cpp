#include "POGGraphicsPCH.h"
#include "IndexBuffer.h"

#include <glad/glad.h>

namespace POG::Graphics
{
	IndexBuffer* IndexBuffer::currentIBO = nullptr;

	IndexBuffer::IndexBuffer()
		: RenderingObject::RenderingObject()
	{
		glGenBuffers(1, &id);
	}

	IndexBuffer::IndexBuffer(const IndexBuffer& indexBuffer)
		: RenderingObject::RenderingObject(indexBuffer)
	{
	}

	IndexBuffer::~IndexBuffer()
	{
		if (GetRefCount() == 1)
		{
			Dispose();
		}
	}

	void IndexBuffer::Dispose()
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