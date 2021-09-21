#include "POGCorePCH.h"
#include "TextControl.h"

#include "POGGraphics.h"

namespace POG::Core
{
	void TextControl::Draw()
	{
		Graphics::RenderText(text, 100.0f, 100.0f, 1.0f, Maths::Vec3(0.0f, 1.0f, 0.0f));
	}
}