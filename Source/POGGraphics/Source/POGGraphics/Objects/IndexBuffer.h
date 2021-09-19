#pragma once

#include "RenderingObject.h"

namespace POG::Graphics
{
	// Bind after desired vao to associate

	class IndexBuffer : public RenderingObject
	{
	public:
		IndexBuffer();
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer(IndexBuffer&&) = delete;

		virtual ~IndexBuffer();

		virtual void Dispose() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual RenderingObject* GetCurrent() override;

		void SetIndexData(const void* indexData, int size);

	private:
		static IndexBuffer* currentIBO;
	};
}

