#pragma once

#include "POGMaths.h"

namespace POG::Graphics
{
    class Texture;

    struct Character 
    {
        Texture*        texture;    // ID handle of the glyph texture
        Maths::Vec2i    size;       // Size of glyph
        Maths::Vec2i    bearing;    // Offset from baseline to left/top of glyph
        unsigned int    advance;    // Offset to advance to next glyph
    };

	void InitText();

    void LoadFont(const char* name, const char* file);

    void RenderText(std::string text, float x, float y, float scale, Maths::Vec3 colour);
}

