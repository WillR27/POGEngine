#include "POGGraphicsPCH.h"
#include "Graphics.h"

#include "POGDebug.h"
#include "POGLog.h"

#include <glad/glad.h>

namespace POG::Graphics
{
	void ErrorCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam)
	{
		POG_ERROR("OpenGL error: {0}", message);

		switch (id)
		{
		case 2100: POG_ERROR("This can be caused by not having a vbo bound before trying to write to a vao.");
		}

		POG_ASSERT(false, "OpenGL error!");
	}

	void Init()
	{
		glDebugMessageCallback(ErrorCallback, nullptr);
		glLineWidth(3.0f);
	}

	void ClearColour(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void ClearColourBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void ClearDepthBuffer()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void DepthTest(bool enable)
	{
		enable ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	}

	void FaceCulling(bool enable)
	{
		enable ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
	}

	void SetPolygonMode(RenderingOption face, RenderingOption type)
	{
		glPolygonMode(face, type);
	}

	void CullFace(RenderingOption face)
	{
		glCullFace(face);
	}

	void SetFrontFace(RenderingOption face)
	{
		glFrontFace(face);
	}

	void Blend(bool enable)
	{
		enable ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void BindDefaultFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderArrays(RenderingOption type, unsigned int first, unsigned int count)
	{
		glDrawArrays(type, first, count);
	}

	void RenderElements(RenderingOption type, unsigned int first, unsigned int count)
	{
		glDrawElements(type, count, GL_UNSIGNED_INT, (void*)(first * sizeof(unsigned int))); // TODO: Remove GL references
	}

	void RenderTrianglesFromArrays(unsigned int first, unsigned int count)
	{
		RenderArrays(POG_TRIANGLES, first, count);
	}

	void RenderTrianglesFromElements(unsigned int first, unsigned int count)
	{
		RenderElements(POG_TRIANGLES, first, count);
	}

	void SetContextAddressFunc(ContextAddressFunc func)
	{
		POG_INFO("Initialising Glad!");
		int success = gladLoadGLLoader((GLADloadproc)func);
		POG_ASSERT(success, "Glad failed to initialise!");
	}
}