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
	{
		SetWidth(width);
		SetHeight(height);
		SetActualWidth(width);
		SetActualHeight(height);
	}

	void Canvas::Draw(Canvas& canvas)
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

		Graphics::DrawRectangle(GetWindowX(), (static_cast<float>(Application::GetInstance().GetHeight()) - GetWindowY()) - GetActualHeight(), GetActualWidth(), GetActualHeight(), { 1.0f, 1.0f, 1.0f });
	}

	void Canvas::CalculateWindowPos(Canvas& canvas)
	{
	}

	void Canvas::CalculateActualSize(Canvas& canvas)
	{
		SetActualWidth(static_cast<float>(Application::GetInstance().GetWidth()) * 2.0f);
		SetActualHeight(static_cast<float>(Application::GetInstance().GetHeight()) * 2.0f);
	}
}