#include "pgepch.h"
#include "Render.h"

#include <glad/glad.h>

namespace PEngine
{
	void Render::Init()
	{
		glDebugMessageCallback(Render::ErrorCallback, nullptr);
	}

	void Render::ErrorCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam)
	{
		PG_ERROR("OpenGL error: {0}", message);

		switch (id)
		{
		case 2100: PG_ERROR("This can be caused by not having a vbo bound before trying to write to a vao.");
		}

		PG_ASSERT(false, "OpenGL error!");
	}

	void Render::EnableDepthTest(bool enable)
	{
		enable ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	}

	void Render::SetPolygonMode(RenderingOption face, RenderingOption type)
	{
		glPolygonMode(face, type);
	}

	void Render::RenderArrays(RenderingOption type, unsigned int first, unsigned int count)
	{
		glDrawArrays(type, first, count);
	}

	void Render::RenderElements(RenderingOption type, unsigned int first, unsigned int count)
	{
		glDrawElements(type, count, GL_UNSIGNED_INT, (void*)(first * sizeof(unsigned int))); // TODO: Remove GL references
	}

	void Render::RenderTrianglesFromArrays(unsigned int first, unsigned int count)
	{
		RenderArrays(PG_TRIANGLES, first, count);
	}

	void Render::RenderTrianglesFromElements(unsigned int first, unsigned int count)
	{
		RenderElements(PG_TRIANGLES, first, count);
	}
	
	unsigned int Render::GetError()
	{
		return glGetError();
	}
}