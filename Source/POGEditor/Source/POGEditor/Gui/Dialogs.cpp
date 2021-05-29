#include "POGEditorPCH.h"
#include "Dialogs.h"

namespace POG::Editor
{
	void ModalDialog::Render()
	{
		if (shouldOpen)
		{
			ImGui::OpenPopup(title);
			shouldOpen = false;
		}

		if (ImGui::BeginPopupModal(title, NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			RenderContent();

			ImGui::EndPopup();
		}
	}

	void ConfirmationDialog::RenderContent()
	{
		ImGui::Text(message);
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();

		for (size_t i = 0; i < buttonNames.size(); i++)
		{
			const char* name = buttonNames[buttonNames.size() - i - 1];
			std::function<void()>& action = buttonActions[buttonNames.size() - i - 1];

			float offset = ImGui::GetWindowWidth() - (DefaultButtonWidth + 10 + i * 90);	
			ImGui::SameLine(offset);

			if (ImGui::Button(name, ImVec2(DefaultButtonWidth, 0)))
			{
				action();
				ImGui::CloseCurrentPopup();
			}
		}
	}
}
