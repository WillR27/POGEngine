#pragma once

#include "POGCore/UI/Control.h"

namespace POG::Core
{
	class TextFieldControl : public Control
	{
	public:
		TextFieldControl();

		virtual ~TextFieldControl() = default;

		virtual void Draw() override;

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

		float textOffset;
		float cursorOffset;

		bool mouseDown;
		float clickedMouseX, clickedMouseY;

		void Type(int key, int mods);
		void Type(char c);

		void CalculateCharacterPositions();
		void CalculateTextOffset();

		void MoveCursorLeft();
		void MoveCursorRight();

		void StartHighlight();
		void CancelHighlight();

		void OnBackspace();
		void OnDelete();

		void DeletePreviousCharacter();
		void DeleteNextCharacter();
		void DeleteSelection();
	};
}

