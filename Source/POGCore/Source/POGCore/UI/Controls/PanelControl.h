#pragma once

#include "POGCore/UI/Control.h"

#include "POGMaths.h"

namespace POG::Core
{
	class PanelControl : public Control
	{
	public:
		PanelControl();

		virtual ~PanelControl() = default;

		virtual void Draw() override;

		Maths::Vec3 GetColour() const { return colour; }
		void SetColour(Maths::Vec3 colour) { this->colour = colour; }

	private:
		Maths::Vec3 colour;
	};
}


