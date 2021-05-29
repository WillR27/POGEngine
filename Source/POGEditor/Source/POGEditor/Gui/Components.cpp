#include "POGEditorPCH.h"
#include "Components.h"

#include <imgui.h>

#include "POGMaths.h"

namespace POG::Editor
{
	void AttachedCamera::Render()
	{
		hasChanged = false;

		ImGui::NewLine();
		ImGui::Text("Camera");

		ImGui::Text("%.3f %.3f %.3f %.3f", camera.camera->GetCameraOrientation().x, camera.camera->GetCameraOrientation().w, camera.camera->GetCameraOrientation().z, camera.camera->GetCameraOrientation().w);
	}

	void Transform::Render()
	{
		hasChanged = false;

		ImGui::NewLine();
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
}
