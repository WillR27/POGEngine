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

		virtual void Update(float dt) override;

		virtual void Draw(float alpha) override;

		virtual void CalculateWindowPos() override;
		virtual void CalculateActualSize() override;

		void OnRawMouseButtonEvent(RawMouseButtonEvent& e);
		void OnRawKeyEvent(RawKeyEvent& e);

		ScaleMode GetScaleMode() const { return scaleMode; }
		void SetScaleMode(ScaleMode scaleMode) { this->scaleMode = scaleMode; }

		float GetScaleX() const { return scaleX; }
		float GetScaleY() const { return scaleY; }

		float GetUnscaledMouseX() const { return unscaledMouseX; }
		float GetUnscaledMouseY() const { return unscaledMouseY; }

		Control& GetFocusedControl() const { return *focusedControl; }
		void SetFocusedControl(Control& control) { this->focusedControl = &control; }

	private:
		ScaleMode scaleMode;
		float scaleX, scaleY;
		float unscaledMouseX, unscaledMouseY;
		Control* focusedControl;
	};
}

