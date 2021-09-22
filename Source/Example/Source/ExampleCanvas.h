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

		virtual void Draw(Canvas& canvas) override;

		POG::Core::PanelControl* panelControl;
	};
}

