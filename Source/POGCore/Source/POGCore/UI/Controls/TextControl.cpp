#include "POGCorePCH.h"
#include "TextControl.h"

#include "POGCore/Application/Application.h"
#include "POGCore/UI/Canvas.h"

#include "POGGraphics.h"

namespace POG::Core
{
	void TextControl::Draw(float alpha)
	{
		if (GetActualWidth() < 0.0f || GetActualHeight() < 0.0f)
		{
			return;
		}

		Graphics::Enable(Graphics::Capability::ScissorTest);
		Graphics::SetScissor(static_cast<int>(GetWindowX()), static_cast<int>((Application::GetInstance().GetHeight() - GetWindowY()) - GetActualHeight()), static_cast<int>(GetActualWidth()), static_cast<int>(GetActualHeight()));
		Graphics::RenderText(text, static_cast<int>(GetWindowX()), static_cast<int>((Application::GetInstance().GetHeight() - GetWindowY()) - GetActualHeight()), 1.0f, Maths::Vec3(0.0f, 1.0f, 0.0f));
		Graphics::Disable(Graphics::Capability::ScissorTest);
	}

	void TextControl::CalculateActualSize()
	{
		Maths::Vec2i size = Graphics::GetTextSize(text, 1.0f);
		SetActualWidth(Maths::Min(GetWidth() * GetCanvas().GetScaleX(), Maths::Min(static_cast<float>(size.x), GetParent().GetActualWidth() - GetX() * GetCanvas().GetScaleX())));
		SetActualHeight(Maths::Min(GetHeight() * GetCanvas().GetScaleY(), Maths::Min(static_cast<float>(size.y), GetParent().GetActualHeight() - GetY() * GetCanvas().GetScaleY())));
	}
}