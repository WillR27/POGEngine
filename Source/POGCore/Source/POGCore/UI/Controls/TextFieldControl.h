#pragma once

#include "POGCore/UI/Control.h"

#include "POGUtil.h"

namespace POG::Core
{
	class TextFieldControl : public Control
	{
	public:
		TextFieldControl();

		virtual ~TextFieldControl() = default;

		virtual void Init() override;

		virtual void Update(float dt) override;

		virtual void Draw(float alpha) override;

		virtual void CalculateActualSize() override;

		void OnMousePressEvent(MousePressEvent& e);
		void OnMouseReleaseEvent(MouseReleaseEvent& e);
		void OnKeyPressEvent(KeyPressEvent& e);
		void OnKeyReleaseEvent(KeyReleaseEvent& e);
		void OnKeyRepeatEvent(KeyRepeatEvent& e);

		std::string GetText() const { return text; }
		void SetText(std::string text) { this->text = text; }

	private:
		std::string text;
		Maths::Vec3 colour;

		std::vector<float> characterPositions;
		int cursorPos;
		int highlightPos;

		Util::Timer<Util::Time::Unit::Seconds, float, true> cursorTimer;

		float textOffset;
		float cursorOffset;

		bool mouseDown;
		float clickedMouseX, clickedMouseY;

		void Type(int key, int mods);
		void Type(char c);

		void MoveCursorLeft();
		void MoveCursorRight();

		void StartHighlight();
		void CancelHighlight();

		void OnBackspace();
		void OnDelete();

		void DeletePreviousCharacter();
		void DeleteNextCharacter();
		void DeleteSelection();

		void CalculateCharacterPositions();
		void CalculateClickAndDrag();
		void CalculateTextOffset();
		void CalculateCursorOffset();
	};
}

