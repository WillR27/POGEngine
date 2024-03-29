#pragma once

namespace POG::Util
{
	using ImageData = unsigned char;
	using Image = ImageData*;

	Image LoadImageFromFile(const char* file, int& width, int& height, int& channels, bool flipVertically = false);
	
	void FreeImage(Image image);
}

