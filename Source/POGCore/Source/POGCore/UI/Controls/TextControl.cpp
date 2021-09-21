#include "POGCorePCH.h"
#include "TextControl.h"

#include "POGCore/Application/Application.h"

#include "POGGraphics.h"

namespace POG::Core
{
	void TextControl::Draw()
	{
		Maths::Vec2i size = Graphics::GetTextSize(text, 1.0f);
		actualHeight = size.y;

		Graphics::RenderText(text, windowX, (Application::GetInstance().GetHeight() - windowY) - actualHeight, 1.0f, Maths::Vec3(0.0f, 1.0f, 0.0f));
	}
}