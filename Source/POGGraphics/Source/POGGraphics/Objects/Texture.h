#pragma once

#include "RenderingObject.h"

namespace POG::Graphics
{
	class Texture : public RenderingObject
	{
	public:
		Texture();
		Texture(const Texture&) = delete;
		Texture(Texture&&) = delete;

		virtual ~Texture();

		virtual void Dispose() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		void SetData(void* data, int width, int height);
		void SetDataRed(void* data, int width, int height);

		void LoadFromImage(const char* file);

		virtual RenderingObject* GetCurrent() override;

		int GetWidth() const { return width; }
		int GetHeight() const { return height; }

	private:
		static Texture* currentFBO;

		int width, height;
	};
}

