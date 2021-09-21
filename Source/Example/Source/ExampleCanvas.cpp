#include "ExamplePCH.h"
#include "ExampleCanvas.h"

using namespace POG;

namespace Example
{
	ExampleCanvas::ExampleCanvas()
		: Core::Canvas(1200, 800, Core::ScaleMode::Fixed)
	{
	}

	void ExampleCanvas::Init()
	{
		auto& textControl = AddControl<Core::TextControl>();
		textControl.SetText("Test text");

		auto& panelControl = AddControl<Core::PanelControl>();
		panelControl.SetColour({1.0f, 1.0f, 0.0f});
	}
}