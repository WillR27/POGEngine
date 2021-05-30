#pragma once

#include "POGRender.h"

namespace POG::Editor
{
	extern Render::Texture* FileIcon;
	extern Render::Texture* FolderIcon;

	void LoadIcons();
	void FreeIcons();
}

