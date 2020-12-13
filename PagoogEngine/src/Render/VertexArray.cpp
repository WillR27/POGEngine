#include "pgepch.h"
#include "VertexArray.h"

#include "glad/glad.h"

namespace PEngine
{
	VertexArray::VertexArray()
		: vao(0)
	{
		glGenVertexArrays(1, &vao);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &vao);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(vao);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::SetAttribute(int index, int numberOfComponents, unsigned int type, bool clamped, int stride, void* offset)
	{
		glVertexAttribPointer(index, numberOfComponents, type, clamped, stride, offset);
		glEnableVertexAttribArray(index);
	}
}