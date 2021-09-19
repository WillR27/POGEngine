#pragma once

#include "RenderingObject.h"

namespace POG::Graphics
{
	// Associated with vao when glVertexAttribPointer is called

	class VertexBuffer : public RenderingObject
	{
	public:
		VertexBuffer();
		VertexBuffer(const VertexBuffer& vertexBuffer);
		VertexBuffer(VertexBuffer&&) = delete;

		virtual ~VertexBuffer();

		virtual void Dispose() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual RenderingObject* GetCurrent() override;

		void SetVertexData(const void* vertexData, unsigned int size);

	private:
		static VertexBuffer* currentVBO;
	};
}

