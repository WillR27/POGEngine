#include "POGEditorPCH.h"
#include "Icons.h"

#include "POGUtil.h"

namespace POG::Editor
{
	Render::Texture* FileIcon = nullptr;
	Render::Texture* FolderIcon = nullptr;

	void LoadIcons()
	{
		int width, height, channels;
		Util::Image image = Util::LoadImage("Resources\\File.png", width, height, channels);
		FileIcon = new Render::Texture();
		FileIcon->SetData(image, width, height);
		Util::FreeImage(image);

		image = Util::LoadImage("Resources\\Folder.png", width, height, channels);
		FolderIcon = new Render::Texture();
		FolderIcon->SetData(image, width, height);
		Util::FreeImage(image);
	}

	void FreeIcons()
	{
		delete FileIcon;
		delete FolderIcon;
	}
}