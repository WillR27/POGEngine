#include "POGGraphicsPCH.h"
#include "Text.h"

#include "POGDebug.h"
#include "POGGraphics.h"
#include "POGLog.h"

#include <ft2build.h>
#include FT_FREETYPE_H  

#include <glad/glad.h>

// https://learnopengl.com/In-Practice/Text-Rendering
// https://www.freetype.org/freetype2/docs/tutorial/step1.html#section-3

namespace POG::Graphics
{
    std::map<const char*, Font> fonts;

    Font* currentFont;

    static Shader shader;

    const char* textVertexShader = R"(
#version 330 core

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
} 		
)";

    const char* textFragmentShader = R"(
#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}  	
)";

	void InitText()
	{
        shader.Init(textVertexShader, textFragmentShader);
	}

    void LoadFont(const char* name, const char* file)
    {
        if (fonts.find(name) != fonts.end())
        {
            POG_WARN("Font \"{0}\" is already loaded!", name);

            return;
        }

        // TODO: Move to proper init
        FT_Library ft;
        if (int error = FT_Init_FreeType(&ft))
        {
            POG_ERROR("Failed to initialise FreeType with error code: {0}", error);
        }

        FT_Face face;
        if (int error = FT_New_Face(ft, file, 0, &face))
        {
            POG_ERROR("Failed to load font with error code: {0}", error);
        }

        FT_Set_Pixel_Sizes(face, 0, 48);

        SetPixelStorei(Alignment::Unpack, 1);

        Font& font = fonts[name];
        auto& chars = font.characters;

        for (unsigned char c = 0; c < 128; c++)
        {
            // load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                POG_ERROR("Failed to load char '{0}' from font \"{1}\"", c, name);
                continue;
            }

            Texture texture;
            texture.SetDataRed(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows);
            Character ch
            {
                texture,
                Maths::Vec2i(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                Maths::Vec2i(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x),
            };

            int ypos = ch.bearing.y - ch.size.y;
            font.minY = ypos < font.minY ? ypos : font.minY;
            font.maxY = ypos + ch.size.y > font.maxY ? ypos + ch.size.y : font.maxY;

            chars.insert({ c, ch });
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        font.vao.Bind();
        font.vbo.Bind();
        font.vbo.SetVertexData(nullptr, sizeof(float) * 6 * 4);
        font.vao.SetAttribute(0, 4, POG_FLOAT, false, 4 * sizeof(float), 0);

        SetPixelStorei(Alignment::Unpack, 4);
    }

    float CalcCharX(const Character& ch, int x, float scale)
    {
        return x + ch.bearing.x * scale;
    }

    float CalcCharY(const Character& ch, int y, float scale)
    {
        return y - (ch.size.y - ch.bearing.y) * scale;
    }

    float CalcCharWidth(const Character& ch, float scale)
    {
        return ch.size.x * scale;
    }

    float CalcCharHeight(const Character& ch, float scale)
    {
        return ch.size.y * scale;
    }

    Maths::Vec2i GetTextSize(std::string text, float scale)
    {
        float x = 0;

        auto& chars = currentFont->characters;
        for (auto c = text.begin(); c != text.end(); c++)
        {
            Character ch = chars[*c];

            x += static_cast<int>((ch.advance >> 6) * scale);
        }

        return { static_cast<int>(x), static_cast<int>((currentFont->maxY - currentFont->minY) * scale) };
    }

	void RenderText(std::string text, int x, int y, float scale, Maths::Vec3 colour)
	{
        Enable(Capability::Blend);
        Enable(Capability::CullFace);
        Disable(Capability::DepthTest);

        Maths::Mat4 projection = glm::ortho(0.0f, WindowWidth, 0.0f, WindowHeight);

        shader.Use();
		shader.SetMatrix4fv("projection", 1, false, Maths::ToData(projection));
		shader.Set3f("textColor", colour.r, colour.g, colour.b);

        currentFont->vao.Bind();

        auto& chars = currentFont->characters;
        for (auto c = text.begin(); c != text.end(); c++)
        {
            Character ch = chars[*c];

            float xpos = CalcCharX(ch, x, scale);
            float ypos = CalcCharY(ch, y, scale) - (currentFont->minY * scale);

            float w = CalcCharWidth(ch, scale);
            float h = CalcCharHeight(ch, scale);

            float vertices[6][4] = 
            {
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };

            ch.texture.Bind();
            currentFont->vbo.Bind();
            currentFont->vbo.SetVertexSubData(vertices, sizeof(vertices));
            RenderTrianglesFromArrays(0, 6);

            x += static_cast<int>((ch.advance >> 6) * scale);
        }

        Enable(Capability::DepthTest);
	}

    void SetFont(const char* name)
    {
        if (fonts.find(name) == fonts.end())
        {
            POG_WARN("Tried to set font to \"{0}\" but it has not been loaded!", name);
        }

        currentFont = &fonts[name];
    }
}