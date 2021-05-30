#include "POGEditorPCH.h"
#include "FilesFolders.h"

#include <imgui.h>

#include "POGUtil.h"

#include "Icons.h"

namespace POG::Editor
{
	void FileFolder::Render()
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

			Render::Texture* texture = isFolder ? FolderIcon : FileIcon;
			ImGui::Image((ImTextureID)((unsigned long long)(*texture)), ImVec2(70.0f, 70.0f));
			ImGui::Text(name.c_str());
		}
		ImGui::EndChildFrame();
		ImGui::PopStyleColor();
	}

	const int FilesFolders::Width = 100;
	const int FilesFolders::Height = 100;

	void FilesFolders::Render()
	{
		if (ImGui::Button("Back"))
		{
			workingDirectory = workingDirectory.parent_path();

			Clear();
			LoadFilesFolders();
		}

		ImGui::SameLine();
		ImGui::Text(workingDirectory.string().c_str());

		float windowWidth = ImGui::GetWindowWidth();
		float totalUsed = 0;

		for (FileFolder& folder : folders)
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

		for (FileFolder& file : files)
		{
			file.Render();

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

		bool changedWorkingDir = false;
		for (FileFolder& folder : folders)
		{
			if (folder.IsDoubleLeftClicked())
			{
				workingDirectory = folder.GetPath();
				changedWorkingDir = true;
				break;
			}
		}

		Clear();
		LoadFilesFolders();
	}

	void FilesFolders::LoadFilesFolders()
	{
		for (const auto& item : std::filesystem::directory_iterator(std::filesystem::path(workingDirectory)))
		{
			if (item.is_directory())
			{
				AddFolder(item.path());
			}
			else
			{
				AddFile(item.path());
			}
		}
	}

	void FilesFolders::AddFile(std::filesystem::path file)
	{
		files.push_back(FileFolder(widgetManager.PopId(), file, Width, Height));
	}

	void FilesFolders::AddFolder(std::filesystem::path folder)
	{
		folders.push_back(FileFolder(widgetManager.PopId(), folder, Width, Height));
	}

	void FilesFolders::Clear()
	{
		files.clear();
		folders.clear();
		widgetManager.Reset();
	}
}
