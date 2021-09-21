#include "POGCorePCH.h"
#include "PanelControl.h"

#include "POGCore/Application/Application.h"

#include "POGGraphics.h"

namespace POG::Core
{
	PanelControl::PanelControl()
		: colour(1.0f, 1.0f, 1.0f)
	{
	}

	void PanelControl::Draw()
	{
		Graphics::DrawRectangle(windowX, (Application::GetInstance().GetHeight() - windowY) - actualHeight, actualWidth, actualHeight, colour);
	}
}