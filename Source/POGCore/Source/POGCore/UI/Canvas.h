#pragma once

#include "Control.h"
#include "UIProperties.h"

namespace POG::Core
{
	class Canvas : public Control
	{
	public:
		Canvas(float width, float height, ScaleMode scaleMode);

		virtual ~Canvas() = default;

		virtual void Init() = 0;

		virtual void Draw(Canvas& canvas) override;

		virtual void CalculateWindowPos(Canvas& canvas) override;
		virtual void CalculateActualSize(Canvas& canvas) override;

		ScaleMode GetScaleMode() const { return scaleMode; }
		void SetScaleMode(ScaleMode scaleMode) { this->scaleMode = scaleMode; }

		float GetScaleX() const { return scaleX; }
		float GetScaleY() const { return scaleY; }

	private:
		ScaleMode scaleMode;
		float scaleX, scaleY;
	};
}

