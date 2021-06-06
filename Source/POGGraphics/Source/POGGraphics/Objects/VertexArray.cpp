#include "POGGraphicsPCH.h"
#include "VertexArray.h"

#include <glad/glad.h>

namespace POG::Graphics
{
	VertexArray* VertexArray::currentVAO= nullptr;

	VertexArray::VertexArray()
		: RenderingObject::RenderingObject()
	{
		glGenVertexArrays(1, &id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(id);
		currentVAO = this;
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	RenderingObject* VertexArray::GetCurrent()
	{
		return currentVAO;
	}

	void VertexArray::SetAttribute(unsigned int index, unsigned int numberOfComponents, unsigned int type, bool clamped, int stride, void* offset)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, numberOfComponents, type, clamped, stride, offset);
	}
}