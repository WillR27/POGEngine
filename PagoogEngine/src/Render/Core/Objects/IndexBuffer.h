#pragma once

#include "RenderingObject.h"

namespace PEngine
{
	// Bind after desired vao to associate

	class IndexBuffer : public RenderingObject
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual RenderingObject* GetCurrent() override;

		void SetIndexData(const void* indexData, int size);

	private:
		static IndexBuffer* currentIBO;
	};
}

