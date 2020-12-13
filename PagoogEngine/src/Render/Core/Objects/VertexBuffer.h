#pragma once

#include "RenderingObject.h"

namespace PEngine
{
	// Associated with vao when glVertexAttribPointer is called

	class VertexBuffer : public RenderingObject
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual RenderingObject* GetCurrent() override;

		void SetVertexData(const void* vertexData, unsigned int size);

	private:
		static VertexBuffer* currentVBO;
	};
}

