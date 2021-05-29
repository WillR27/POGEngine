#include "POGEditorPCH.h"
#include "Text.h"

namespace POG::Editor
{
	void TextField::Render()
	{
		ImGui::InputText(label, text, maxLength);
	}
}