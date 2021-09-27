#include "POGCorePCH.h"
#include "Canvas.h"

#include "POGCore/Application/Application.h"

#include "POGGraphics.h"

namespace POG::Core
{
	Canvas::Canvas(float width, float height, ScaleMode scaleMode)
		: Control::Control()
		, scaleMode(scaleMode)
		, scaleX(1.0f)
		, scaleY(1.0f)
		, unscaledMouseX(0.0f)
		, unscaledMouseY(0.0f)
		, focusedControl(this)
	{
		this->canvas = this;

		SetWidth(width);
		SetHeight(height);
		SetActualWidth(width);
		SetActualHeight(height);
	}

	void Canvas::Draw()
	{
		if (scaleMode == ScaleMode::Stretch)
		{
			scaleX = static_cast<float>(Application::GetInstance().GetWidth()) / GetWidth();
			scaleY = static_cast<float>(Application::GetInstance().GetHeight()) / GetHeight();
		}
		else
		{
			scaleX = 1.0f;
			scaleY = 1.0f;
		}

		// TODO: Move and call before input handling
		unscaledMouseX = Mouse::GetX() / scaleX;
		unscaledMouseY = Mouse::GetY() / scaleY;

		Graphics::DrawRectangle(GetWindowX(), (static_cast<float>(Application::GetInstance().GetHeight()) - GetWindowY()) - GetActualHeight(), GetActualWidth(), GetActualHeight(), { 1.0f, 1.0f, 1.0f });
	}

	void Canvas::CalculateWindowPos()
	{
	}

	void Canvas::CalculateActualSize()
	{
		SetActualWidth(static_cast<float>(Application::GetInstance().GetWidth()) * 2.0f);
		SetActualHeight(static_cast<float>(Application::GetInstance().GetHeight()) * 2.0f);
	}

	void Canvas::OnRawMouseButtonEvent(RawMouseButtonEvent& e)
	{
		RawMouseButtonEvent eCopy = e;

		Control::OnRawMouseButtonEvent(eCopy);
	}
}