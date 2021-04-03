#include "POGRenderPCH.h"
#include "Render.h"

#include "POGDebug.h"
#include "POGLog.h"

#include <glad/glad.h>

namespace POG::Render
{
	void Render::ClearColour(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Render::ClearColourBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Render::ClearDepthBuffer()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void Render::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void Render::SetContextAddressFunc(ContextAddressFunc func)
	{
		POG_INFO("Initialising Glad!");
		int success = gladLoadGLLoader((GLADloadproc)func);
		POG_ASSERT(success, "Glad failed to initialise!");
	}
}