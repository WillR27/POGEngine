#pragma once

#include "POGCore.h"

namespace Example
{
	class ExampleCanvas : public POG::Core::Canvas
	{
	public:
		ExampleCanvas();

		virtual ~ExampleCanvas() = default;

		virtual void Init() override;

		virtual void Draw(float alpha) override;

		void PanelControl_OnMouseReleaseEvent(POG::Core::MouseReleaseEvent& e);
		void PanelControl_OnMousePressEvent(POG::Core::MousePressEvent& e);

		void PanelControl2_OnMouseReleaseEvent(POG::Core::MouseReleaseEvent& e);
		void PanelControl2_OnMousePressEvent(POG::Core::MousePressEvent& e);

		POG::Core::PanelControl* panelControl;
		POG::Core::PanelControl* panelControl2;
	};
}

