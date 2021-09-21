#pragma once

#include "Control.h"
#include "UIProperties.h"

namespace POG::Core
{
	class Canvas : public Control
	{
	public:
		Canvas(int width, int height, ScaleMode scaleMode);

		virtual ~Canvas() = default;

		virtual void Init() = 0;

		virtual void Draw() override;

	protected:
		ScaleMode scaleMode;
	};
}

