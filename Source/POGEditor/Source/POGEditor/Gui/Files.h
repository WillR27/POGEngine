#pragma once

#include <vector>

#include "Widget.h"

namespace POG::Editor
{
	class Folder
	{
	public:
		Folder(int id, const char* name, float width, float height)
			: id(id)
			, name(name)
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
		
		bool IsHovered() { return isHovered; }
		bool WasHovered() { return wasHovered; }

		bool IsLeftClicked() { return isLeftClicked; }
		bool IsDoubleLeftClicked() { return isDoubleLeftClicked; }
		bool IsRightClicked() { return isRightClicked; }

	private:
		int id;
		const char* name;
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
		FilesFolders()
			: widgetManager(1000)
			, folders()
		{
		}

		void Render();

		void AddFile(const char* file);
		void AddFolder(const char* folder);

		void Clear();

	private:
		static const int Width, Height;

		WidgetManager widgetManager;

		std::vector<Folder> folders;
	};
}