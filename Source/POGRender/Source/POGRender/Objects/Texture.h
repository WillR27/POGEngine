#pragma once

#include "RenderingObject.h"

namespace POG::Render
{
	class Texture : public RenderingObject
	{
	public:
		Texture();
		Texture(const Texture&) = delete;
		Texture(Texture&&) = delete;

		virtual ~Texture();

		virtual void Bind() override;
		virtual void Unbind() override;

		void SetData(void* data, int width, int height);

		virtual RenderingObject* GetCurrent() override;

	private:
		static Texture* currentFBO;
	};
}

