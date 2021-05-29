#include "POGEditorPCH.h"
#include "Components.h"

#include <imgui.h>

#include "POGMaths.h"

namespace POG::Editor
{
	void Transform::Render()
	{
		hasChanged = false;

		ImGui::BeginChild("Transform");
		{
			ImGui::Text("Transform");

			ImGui::InputFloat3("Position", Maths::ToDataRef(transform.position));
			if (ImGui::IsItemDeactivatedAfterEdit())
			{
				SetChanged();
			}

			ImGui::InputFloat4("Orientation", Maths::ToDataRef(transform.orientation));
			if (ImGui::IsItemDeactivatedAfterEdit())
			{
				SetChanged();
			}

			ImGui::InputFloat3("Scale", Maths::ToDataRef(transform.scale));
			if (ImGui::IsItemDeactivatedAfterEdit())
			{
				SetChanged();
			}
		}
		ImGui::EndChild();
	}
}
