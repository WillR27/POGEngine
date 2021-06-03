#include "POGUtilPCH.h"
#include "Images.h"

#include <stb_image.h>

namespace POG::Util
{
	Image LoadImageFromFile(const char* file, int& width, int& height, int& channels, bool flipVertically)
	{
		stbi_set_flip_vertically_on_load(flipVertically);

		return stbi_load(file, &width, &height, &channels, STBI_rgb_alpha);
	}

	void FreeImage(Image image)
	{
		stbi_image_free(image);
	}
}