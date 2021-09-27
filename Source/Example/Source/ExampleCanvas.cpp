#include "ExamplePCH.h"
#include "ExampleCanvas.h"

using namespace POG;

namespace Example
{
	ExampleCanvas::ExampleCanvas()
		: Core::Canvas(1200.0f, 800.0f, Core::ScaleMode::Stretch)
	{
	}

	void ExampleCanvas::Init()
	{
		panelControl = &AddControl<Core::PanelControl>();
		panelControl->SetWidth(300.0f);
		panelControl->SetHeight(200.0f);
		panelControl->SetX(100.0f);
		panelControl->SetY(200.0f);
		panelControl->SetColour({ 1.0f, 1.0f, 0.0f });
		panelControl->SetAnchor(Core::Anchor::None);

		panelControl2 = &panelControl->AddControl<Core::PanelControl>();
		panelControl2->SetWidth(100.0f);
		panelControl2->SetX(70.0f);
		panelControl2->SetY(100.0f);
		panelControl2->SetColour({ 0.0f, 0.0f, 1.0f });
		panelControl2->SetAnchor(Core::Anchor::Left | Core::Anchor::Right | Core::Anchor::Bottom);

		auto& textControl = panelControl2->AddControl<Core::TextControl>();
		textControl.SetX(20.0f);
		textControl.SetY(40.0f);
		textControl.SetAnchor(Core::Anchor::Left | Core::Anchor::Bottom | Core::Anchor::Right);
		textControl.SetText("Cut off text");

		panelControl->GetEventBus().Subscribe(&ExampleCanvas::PanelControl_OnMouseReleaseEvent, this);
		panelControl->GetEventBus().Subscribe(&ExampleCanvas::PanelControl_OnMousePressEvent, this);

		panelControl2->GetEventBus().Subscribe(&ExampleCanvas::PanelControl2_OnMouseReleaseEvent, this);
		panelControl2->GetEventBus().Subscribe(&ExampleCanvas::PanelControl2_OnMousePressEvent, this);
	}

	void ExampleCanvas::Draw()
	{
		//panelControl->SetWidth(panelControl->GetWidth() + 2);
		//panelControl->SetHeight(panelControl->GetHeight() + 1);

		Canvas::Draw();
	}

	void ExampleCanvas::PanelControl_OnMouseReleaseEvent(POG::Core::MouseReleaseEvent& e)
	{
		panelControl->SetColour({ 1.0f, 0.0f, 1.0f });
	}

	void ExampleCanvas::PanelControl_OnMousePressEvent(POG::Core::MousePressEvent& e)
	{
		panelControl->SetColour({ 0.0f, 1.0f, 0.0f });
	}

	void ExampleCanvas::PanelControl2_OnMouseReleaseEvent(POG::Core::MouseReleaseEvent& e)
	{
		panelControl2->SetColour({ 1.0f, 0.0f, 0.5f });
	}

	void ExampleCanvas::PanelControl2_OnMousePressEvent(POG::Core::MousePressEvent& e)
	{
		panelControl2->SetColour({ 1.0f, 0.5f, 0.0f });
	}
}