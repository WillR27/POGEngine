#include "POGEditorPCH.h"
#include "Files.h"

#include <imgui.h>

namespace POG::Editor
{
	void Folder::Render()
	{
		wasHovered = isHovered;
		isHovered = false;

		isLeftClicked = false;
		isDoubleLeftClicked = false;
		isRightClicked = false;

		ImGui::PushStyleColor(ImGuiCol_FrameBg, wasHovered ? ImVec4(0.2f, 0.9f, 1.0f, 0.5f) : ImVec4(0.5f, 0.5f, 1.0f, 0.5f));
		ImGui::BeginChildFrame(id, ImVec2(100.0f, 100.0f));
		{
			if (ImGui::IsWindowHovered())
			{
				isHovered = true;
				isLeftClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left);
				isDoubleLeftClicked = ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left);
				isRightClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Right);
			}

			ImGui::Image((ImTextureID)1, ImVec2(30.0f, 30.0f), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::Text(isLeftClicked ? "egggggg" : name);
			ImGui::Text(isDoubleLeftClicked ? "egggggg" : name);
		}
		ImGui::EndChildFrame();
		ImGui::PopStyleColor();
	}

	const int FilesFolders::Width = 100;
	const int FilesFolders::Height = 100;

	void FilesFolders::Render()
	{
		float windowWidth = ImGui::GetWindowWidth();
		float totalUsed = 0;

		for (Folder& folder : folders)
		{
			folder.Render();

			totalUsed += Width;

			if (totalUsed + Width < windowWidth)
			{
				ImGui::SameLine();
			}
			else
			{
				totalUsed = 0;
			}
		}
	}

	void FilesFolders::AddFile(const char* file)
	{
		
	}

	void FilesFolders::AddFolder(const char* folder)
	{
		
		folders.push_back(Folder(widgetManager.PopId(), folder, Width, Height));
	}

	void FilesFolders::Clear()
	{
		folders.clear();
		widgetManager.Reset();
	}
}
