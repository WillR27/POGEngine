#include "POGEditorPCH.h"
#include "FilesFolders.h"

#include <imgui.h>

#include "POGUtil.h"

#include "Icons.h"
#include "Styles.h"

namespace POG::Editor
{
	const float FilesFolders::Width = 100.0f;
	const float FilesFolders::Height = 140.0f;

	void FileFolder::Render()
	{
		isHovered = false;
		isLeftClicked = false;
		isDoubleLeftClicked = false;
		isRightClicked = false;

		float framePaddingX = 0.0f;
		float framePaddingY = 0.0f;
		float imageWidth = width - framePaddingX * 2.0f;
		float imageHeight = height - framePaddingY * 2.0f - 40.0f;

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(framePaddingX, framePaddingY));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, isSelected ? 1.0f : 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, Transparent);
		ImGui::BeginChildFrame(id, ImVec2(width, height), ImGuiWindowFlags_NoScrollbar);
		{
			if (ImGui::IsWindowHovered())
			{
				isHovered = true;
				isLeftClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left);
				isDoubleLeftClicked = ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left);
				isRightClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Right);
			}

			Render::Texture* texture = isFolder ? FolderIcon : FileIcon;
			ImGui::Image((ImTextureID)((unsigned long long)(*texture)), ImVec2(imageWidth, imageHeight));
			
			const float textPadding = 5.0f;
			const int charsToStrip = 4;

			float textWidth = ImGui::CalcTextSize(displayName.c_str()).x;
			while (textWidth > width - textPadding)
			{
				displayName2 = displayName.substr(displayName.size() - charsToStrip, charsToStrip) + displayName2;
				displayName.erase(displayName.size() - charsToStrip);

				textWidth = ImGui::CalcTextSize(displayName.c_str()).x;
			}
			
			float textWidth2 = ImGui::CalcTextSize(displayName2.c_str()).x;
			while (textWidth2 > width - textPadding)
			{
				displayName2.erase(displayName2.size() - charsToStrip);
				displayName2 += "...";

				textWidth2 = ImGui::CalcTextSize(displayName2.c_str()).x;
			}

			ImGui::Indent(width / 2.0f - textWidth / 2.0f);
			ImGui::Text(displayName.c_str());
			ImGui::Indent(-(width / 2.0f - textWidth / 2.0f));

			ImGui::Indent(width / 2.0f - textWidth2 / 2.0f);
			ImGui::Text(displayName2.c_str());
			ImGui::Indent(-(width / 2.0f - textWidth2 / 2.0f));
		}
		ImGui::EndChildFrame();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(3);
	}

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
		float widthPlusSpacing = Width + ItemSpacingRight;
		float totalUsed = WindowPaddingX;

		FileFolder* newlySelected = nullptr;

		for (FileFolder& folder : folders)
		{
			folder.Render();
			
			if (!newlySelected && !folder.IsSelected() && (folder.IsLeftClicked() || folder.IsDoubleLeftClicked() || folder.IsRightClicked()))
			{
				folder.SetSelected(true);
				newlySelected = &folder;
			}

			totalUsed += widthPlusSpacing;

			if (totalUsed + widthPlusSpacing < windowWidth)
			{
				ImGui::SameLine();
			}
			else
			{
				totalUsed = WindowPaddingX;
			}
		}

		for (FileFolder& file : files)
		{
			file.Render();

			if (!newlySelected && !file.IsSelected() && (file.IsLeftClicked() || file.IsDoubleLeftClicked() || file.IsRightClicked()))
			{
				file.SetSelected(true);
				newlySelected = &file;
			}

			totalUsed += widthPlusSpacing;

			if (totalUsed + widthPlusSpacing < windowWidth)
			{
				ImGui::SameLine();
			}
			else
			{
				totalUsed = WindowPaddingX;
			}
		}

		if (newlySelected != nullptr)
		{
			for (FileFolder& folder : folders)
			{
				if (&folder != newlySelected)
				{
					folder.SetSelected(false);
				}
			}

			for (FileFolder& file : files)
			{
				if (&file != newlySelected)
				{
					file.SetSelected(false);
				}
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

		if (changedWorkingDir)
		{
			Clear();
			LoadFilesFolders();
		}
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
