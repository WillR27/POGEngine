#include "POGRenderPCH.h"
#include "Render.h"

#include "POGDebug.h"
#include "POGLog.h"

#include <glad/glad.h>

namespace POG::Render
{
	void Render::ErrorCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam)
	{
		POG_ERROR("OpenGL error: {0}", message);

		switch (id)
		{
		case 2100: POG_ERROR("This can be caused by not having a vbo bound before trying to write to a vao.");
		}

		POG_ASSERT(false, "OpenGL error!");
	}

	void Render::Init()
	{
		glDebugMessageCallback(Render::ErrorCallback, nullptr);
	}

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