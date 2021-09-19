#pragma once

#include "RenderingObject.h"
#include "Texture.h"

namespace POG::Graphics
{
	class FrameBuffer : public RenderingObject
	{
	public:
		FrameBuffer();
		FrameBuffer(const FrameBuffer&) = delete;
		FrameBuffer(FrameBuffer&&) = delete;

		virtual ~FrameBuffer();

		virtual void Dispose() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		void BindTexture(const Texture& texture);

		virtual RenderingObject* GetCurrent() override;

	private:
		static FrameBuffer* currentFBO;
	};
}

