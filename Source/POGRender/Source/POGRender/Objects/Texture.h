#pragma once

#include "RenderingObject.h"

namespace POG::Render
{
	class Texture : public RenderingObject
	{
	public:
		Texture();
		~Texture();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual RenderingObject* GetCurrent() override;

	private:
		static Texture* currentFBO;
	};
}

