#pragma once

#include "PagoogCommon.h"

#include "PagoogRenderAPI.h"

namespace Pagoog::Render
{
	class PG_RENDER_API Render
	{
	public:
		static void ClearColour(float r, float g, float b, float a);

		static void ClearColourBuffer();
		static void ClearDepthBuffer();

		static void SetViewport(int x, int y, int width, int height);

		static void SetContextAddressFunc(ContextAddressFunc func);
	};
}

