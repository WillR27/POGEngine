#pragma once

#include "POGCore/UI/Control.h"

namespace POG::Core
{
	class TextControl : public Control
	{
	public:
		TextControl() = default;

		virtual ~TextControl() = default;

		virtual void Draw() override;

		std::string GetText() const { return text; }
		void SetText(std::string text) { this->text = text; }

	private:
		std::string text;
	};
}

