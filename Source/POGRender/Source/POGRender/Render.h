#pragma once

#include "POGCommon.h"

#include "POGRenderAPI.h"

namespace POG::Render
{
	void ErrorCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam);

	void Init();

	void ClearColour(float r, float g, float b, float a);

	void ClearColourBuffer();
	void ClearDepthBuffer();

	void SetViewport(int x, int y, int width, int height);

	void BindDefaultFrameBuffer();

	void SetContextAddressFunc(ContextAddressFunc func);
}

