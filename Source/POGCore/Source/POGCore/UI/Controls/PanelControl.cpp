#include "POGCorePCH.h"
#include "PanelControl.h"

#include "POGCore/Application/Application.h"
#include "POGCore/UI/Canvas.h"

#include "POGGraphics.h"

namespace POG::Core
{
	PanelControl::PanelControl()
		: colour(1.0f, 1.0f, 1.0f)
	{
	}

	void PanelControl::Draw(Canvas& canvas)
	{
		if (GetActualWidth() < 0.0f || GetActualHeight() < 0.0f)
		{
			return;
		}

		Graphics::DrawRectangle(GetWindowX(), (Application::GetInstance().GetHeight() - GetWindowY()) - GetActualHeight(), GetActualWidth(), GetActualHeight(), colour);
	}
}