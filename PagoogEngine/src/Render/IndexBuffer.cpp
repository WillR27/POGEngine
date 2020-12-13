#include "pgepch.h"
#include "IndexBuffer.h"

#include "glad/glad.h"

namespace PEngine
{
	IndexBuffer::IndexBuffer()
		: ibo(0)
	{
		glGenBuffers(1, &ibo);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &ibo);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::SetIndexData(const void* indexData, int size)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indexData, GL_STATIC_DRAW);
	}
}