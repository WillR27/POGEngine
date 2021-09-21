#include "POGCorePCH.h"
#include "Canvas.h"

#include "POGLog.h"

namespace POG::Core
{
	Canvas::Canvas(int width, int height, ScaleMode scaleMode)
		: Control::Control()
		, scaleMode(scaleMode)
	{
		this->width = width;
		this->height = height;
	}

	void Canvas::Draw()
	{
		for (Control* control : children)
		{
			control->Draw();
		}
	}
}