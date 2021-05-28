#include "POGEditorPCH.h"
#include "GuiUtil.h"

namespace POG::Editor
{
	bool ConfirmationDialog(const char* title, const char* message)
	{
		ImGui::OpenPopup("ImportAssetDialog");

		if (ImGui::BeginPopupModal("ImportAssetDialog"))
		{
			ImGui::Text("test");
		}

		return false;
	}
}