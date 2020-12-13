#include "pgepch.h"
#include "VertexBuffer.h"

#include "glad/glad.h"

namespace PEngine
{
	VertexBuffer::VertexBuffer()
		: vbo(0)
	{
		glGenBuffers(1, &vbo);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &vbo);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::SetVertexData(const void* vertexData, unsigned int size)
	{
		glBufferData(GL_ARRAY_BUFFER, size, vertexData, GL_STATIC_DRAW);
	}
}