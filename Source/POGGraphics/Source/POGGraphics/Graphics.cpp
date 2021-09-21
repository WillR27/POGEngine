#include "POGGraphicsPCH.h"
#include "Graphics.h"

#include "POGGraphics/Drawing/Drawing.h"
#include "POGGraphics/Text/Text.h"

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

	void Enable(Capability capability)
	{
		glEnable(static_cast<GLenum>(capability));
	}

	void Disable(Capability capability)
	{
		glDisable(static_cast<GLenum>(capability));
	}

	bool IsEnabled(Capability capability)
	{
		return glIsEnabled(static_cast<GLenum>(capability));
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

	PolygonMode CurrentPolygonModeFront = PolygonMode::Fill;
	PolygonMode CurrentPolygonModeBack = PolygonMode::Fill;
	PolygonMode GetPolygonMode(PolygonFace face) { return face == PolygonFace::Back ? CurrentPolygonModeBack : CurrentPolygonModeFront; }

	void SetPolygonMode(PolygonFace face, PolygonMode mode)
	{
		if (face == PolygonFace::Front) CurrentPolygonModeFront = mode;
		else if (face == PolygonFace::Back) CurrentPolygonModeBack = mode;
		else { CurrentPolygonModeFront = mode; CurrentPolygonModeBack = mode; }
		glPolygonMode(static_cast<GLenum>(face), static_cast<GLenum>(mode));
	}

	PolygonFaceDirection CurrentFrontFaceDirection = PolygonFaceDirection::Clockwise;
	PolygonFaceDirection GetFrontFaceDirection() { return CurrentFrontFaceDirection; }

	void SetFrontFaceDirection(PolygonFaceDirection direction)
	{
		CurrentFrontFaceDirection = direction;
		glFrontFace(static_cast<GLenum>(direction));
	}

	PolygonFace CurrentCullFace = PolygonFace::Back;
	PolygonFace GetCullFace() { return CurrentCullFace; }

	void SetCullFace(PolygonFace face)
	{
		CurrentCullFace = face;
		glCullFace(static_cast<GLenum>(face));
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

	void SetPixelStorei(Alignment alignment, int value)
	{
		glPixelStorei(static_cast<GLenum>(alignment), value);
	}

	void SetPixelStoref(Alignment alignment, float value)
	{
		glPixelStoref(static_cast<GLenum>(alignment), value);
	}

	void SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void BindDefaultFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void SetContextAddressFunc(ContextAddressFunc func)
	{
		POG_INFO("Initialising Glad!");
		int success = gladLoadGLLoader((GLADloadproc)func);
		POG_ASSERT(success, "Glad failed to initialise!");
	}

	float WindowWidth = 1200.0f;
	float WindowHeight = 800.0f;

	void SetWindowWidthHeight(float width, float height)
	{
		WindowWidth = width;
		WindowHeight = height;
	}

	void Init()
	{
		glDebugMessageCallback(ErrorCallback, nullptr);
		glLineWidth(3.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		SetPolygonMode(PolygonFace::Front, CurrentPolygonModeFront);
		SetPolygonMode(PolygonFace::Back, CurrentPolygonModeBack);
		SetFrontFaceDirection(CurrentFrontFaceDirection);
		SetCullFace(CurrentCullFace);

		Enable(Graphics::Capability::Blend);
		Enable(Graphics::Capability::CullFace);
		Enable(Graphics::Capability::DepthTest);

		InitDrawing();
		InitText();
	}
}