#pragma once

#include <imgui.h>

namespace POG::Editor
{
	class TextField
	{
	public:
		TextField(const char* label = "", size_t maxLength = 128)
			: label(label)
			, maxLength(maxLength)
			, text(new char[maxLength])
		{
		}

		virtual ~TextField()
		{
			delete[] text;
		}

		void Render();
		bool HasFinishedEditing() { return ImGui::IsItemDeactivatedAfterEdit(); }

		const char* GetText() const { return text; }
		void SetText(char* text) { this->text = text; }

	private:
		const char* label;
		size_t maxLength;

		char* text;
	};
}

