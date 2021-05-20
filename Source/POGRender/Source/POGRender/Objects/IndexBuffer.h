#pragma once

#include "RenderingObject.h"

namespace POG::Render
{
	// Bind after desired vao to associate

	class IndexBuffer : public RenderingObject
	{
	public:
		IndexBuffer();
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer(IndexBuffer&&) = delete;

		~IndexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual RenderingObject* GetCurrent() override;

		void SetIndexData(const void* indexData, int size);

	private:
		static IndexBuffer* currentIBO;
	};
}

