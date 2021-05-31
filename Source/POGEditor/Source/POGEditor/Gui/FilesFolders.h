#pragma once

#include <filesystem>
#include <vector>

#include "Widget.h"

namespace POG::Editor
{
	class FileFolder
	{
	public:
		FileFolder(int id, std::filesystem::path path, float width, float height)
			: id(id)
			, path(path)
			, fileName(path.filename().string())
			, displayName(fileName)
			, displayName2("")
			, width(width)
			, height(height)
			, isFolder(std::filesystem::is_directory(path))
			, isHovered(false)
			, isLeftClicked(false)
			, isDoubleLeftClicked(false)
			, isRightClicked(false)
			, isSelected(false)
		{
		}

		void Render();
		
		std::filesystem::path GetPath() { return path; }

		bool IsHovered() { return isHovered; }
		bool IsLeftClicked() { return isLeftClicked; }
		bool IsDoubleLeftClicked() { return isDoubleLeftClicked; }
		bool IsRightClicked() { return isRightClicked; }

		bool IsSelected() const { return isSelected; }
		void SetSelected(bool isSelected) { this->isSelected = isSelected; }

	private:
		int id;
		std::filesystem::path path;
		std::string fileName;
		std::string displayName, displayName2;
		float width, height;
		bool isFolder;

		bool isHovered;
		bool isLeftClicked;
		bool isDoubleLeftClicked;
		bool isRightClicked;

		bool isSelected;
	};

	class FilesFolders
	{
	public:
		FilesFolders(std::filesystem::path workingDirectory)
			: workingDirectory(workingDirectory)
			, widgetManager(1000)
			, files()
			, folders()
		{
			LoadFilesFolders();
		}

		void Render();

	private:
		static const float Width, Height;

		std::filesystem::path workingDirectory;

		WidgetManager widgetManager;

		std::vector<FileFolder> files;
		std::vector<FileFolder> folders;

		void LoadFilesFolders();

		void AddFile(std::filesystem::path file);
		void AddFolder(std::filesystem::path folder);

		void Clear();
	};
}