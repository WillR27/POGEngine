#pragma once

#include "POGCore/UI/Control.h"

namespace POG::Core
{
	class TextControl : public Control
	{
	public:
		TextControl() = default;

		virtual ~TextControl() = default;

		virtual void Draw(Canvas& canvas) override;

		virtual void CalculateActualSize(Canvas& canvas) override;

		std::string GetText() const { return text; }
		void SetText(std::string text) { this->text = text; }

	private:
		std::string text;
	};
}

