#pragma once

#include "POGGraphics/Objects/VertexArray.h"
#include "POGGraphics/Objects/VertexBuffer.h"
#include "POGGraphics/Objects/Texture.h"

#include "POGMaths.h"

namespace POG::Graphics
{
    class Texture;

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
        VertexArray vao;
        VertexBuffer vbo;
    };

	void InitText();

    void LoadFont(const char* name, const char* file);

    void RenderText(std::string text, float x, float y, float scale, Maths::Vec3 colour);
}

