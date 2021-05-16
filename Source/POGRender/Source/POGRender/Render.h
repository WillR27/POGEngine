#pragma once

#include "POGCommon.h"

#include "POGRenderAPI.h"

namespace POG::Render
{
	class Render
	{
	public:
		static void ErrorCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam);

		static void Init();

		static void ClearColour(float r, float g, float b, float a);

		static void ClearColourBuffer();
		static void ClearDepthBuffer();

		static void SetViewport(int x, int y, int width, int height);

		static void SetContextAddressFunc(ContextAddressFunc func);
	};
}

