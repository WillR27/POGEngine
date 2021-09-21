#pragma once

#include "POGGraphics/Objects/VertexArray.h"
#include "POGGraphics/Objects/VertexBuffer.h"
#include "POGGraphics/Objects/Texture.h"

#include "POGMaths.h"

namespace POG::Graphics
{
    struct Character 
    {
        Texture         texture;    // ID handle of the glyph texture
        Maths::Vec2i    size;       // Size of glyph
        Maths::Vec2i    bearing;    // Offset from baseline to left/top of glyph
        unsigned int    advance;    // Offset to advance to next glyph
    };

    struct Font
    {
        std::map<char, Character> characters;
        int minY, maxY;
        VertexArray vao;
        VertexBuffer vbo;
    };

	void InitText();

    void LoadFont(const char* name, const char* file);

    Maths::Vec2i GetTextSize(std::string text, float scale);

    void RenderText(std::string text, int x, int y, float scale, Maths::Vec3 colour);

    void SetFont(const char* name);
}

