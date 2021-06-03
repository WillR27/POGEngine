﻿#include "POGEditorPCH.h"
#include "Icons.h"

#include "POGUtil.h"

namespace POG::Editor
{
	Render::Texture* FileIcon = nullptr;
	Render::Texture* FolderIcon = nullptr;

	void LoadIcons()
	{
		LoadIcon(FileIcon, "Resources\\File.png");
		LoadIcon(FolderIcon, "Resources\\Folder.png");
	}

	void FreeIcons()
	{
		delete FileIcon;
		delete FolderIcon;
	}

	void LoadIcon(Render::Texture*& texture, const char* file)
	{
		int width, height, channels;
		Util::Image image = Util::LoadImageFromFile(file, width, height, channels);
		texture = new Render::Texture();
		texture->SetData(image, width, height);
		Util::FreeImage(image);
	}
}