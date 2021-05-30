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
			, name(path.filename().string())
			, width(width)
			, height(height)
			, isHovered(false)
			, wasHovered(false)
			, isLeftClicked(false)
			, isDoubleLeftClicked(false)
			, isRightClicked(false)
		{
		}

		void Render();
		
		std::filesystem::path GetPath() { return path; }

		bool IsHovered() { return isHovered; }
		bool WasHovered() { return wasHovered; }

		bool IsLeftClicked() { return isLeftClicked; }
		bool IsDoubleLeftClicked() { return isDoubleLeftClicked; }
		bool IsRightClicked() { return isRightClicked; }

	private:
		int id;
		std::filesystem::path path;
		std::string name;
		float width, height;

		bool isHovered;
		bool wasHovered;

		bool isLeftClicked;
		bool isDoubleLeftClicked;
		bool isRightClicked;
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
		static const int Width, Height;

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