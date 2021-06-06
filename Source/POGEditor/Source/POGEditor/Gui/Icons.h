#pragma once

#include "POGGraphics.h"

namespace POG::Editor
{
	extern Graphics::Texture* FileIcon;
	extern Graphics::Texture* FolderIcon;

	void LoadIcons();
	void FreeIcons();

	void LoadIcon(Graphics::Texture*& texture, const char* file);
}

