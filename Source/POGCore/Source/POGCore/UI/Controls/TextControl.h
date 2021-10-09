#pragma once

#include "POGCore/UI/Control.h"

namespace POG::Core
{
	class TextControl : public Control
	{
	public:
		TextControl() = default;

		virtual ~TextControl() = default;

		virtual void Draw(float alpha) override;

		virtual void CalculateActualSize() override;

		std::string GetText() const { return text; }
		void SetText(std::string text) { this->text = text; }

	private:
		std::string text;
	};
}

