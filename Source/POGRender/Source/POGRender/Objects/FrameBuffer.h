#pragma once

#include "RenderingObject.h"
#include "Texture.h"

namespace POG::Render
{
	class FrameBuffer : public RenderingObject
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		void BindTexture(const Texture& texture);

		virtual RenderingObject* GetCurrent() override;

	private:
		static FrameBuffer* currentFBO;
	};
}

