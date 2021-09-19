#include "POGGraphicsPCH.h"
#include "Text.h"

#include "POGDebug.h"
#include "POGGraphics.h"
#include "POGLog.h"

#include <ft2build.h>
#include FT_FREETYPE_H  

#include <glad/glad.h>

namespace POG::Graphics
{
    std::map<const char*, Font> fonts;

    float windowWidth = 1200.0f;
    float windowHeight = 800.0f;

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

    Shader shader;

	void InitText()
	{
        shader.Init(textVertexShader, textFragmentShader);
	}

    void LoadFont(const char* name, const char* file)
    {
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

        // TODO: Check if font already exists
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
            Character character
            {
                texture,
                Maths::Vec2i(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                Maths::Vec2i(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x),
            };
            chars.insert({ c, character });
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        font.vao.Bind();
        font.vbo.Bind();
        font.vbo.SetVertexData(nullptr, sizeof(float) * 6 * 4);
        font.vao.SetAttribute(0, 4, POG_FLOAT, false, 4 * sizeof(float), 0);

        SetPixelStorei(Alignment::Unpack, 4);
    }

	void RenderText(std::string text, float x, float y, float scale, Maths::Vec3 colour)
	{
        Enable(Capability::Blend);
        Enable(Capability::CullFace);
        Disable(Capability::DepthTest);

        glm::mat4 projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight);
        shader.Use();
		shader.SetMatrix4fv("projection", 1, false, Maths::ToData(projection));
		shader.Set3f("textColor", colour.r, colour.g, colour.b);

        Font& font = fonts["Arial"];
        auto& chars = font.characters;

        font.vao.Bind();

        for (auto c = text.begin(); c != text.end(); c++)
        {
            Character ch = chars[*c];

            float xpos = x + ch.bearing.x * scale;
            float ypos = y - (ch.size.y - ch.bearing.y) * scale;

            float w = ch.size.x * scale;
            float h = ch.size.y * scale;

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
            font.vbo.Bind();
            font.vbo.SetVertexSubData(vertices, sizeof(vertices));
            RenderTrianglesFromArrays(0, 6);

            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }

        Enable(Capability::DepthTest);
	}

    void SetWindowWidthHeight(float width, float height)
    {
        windowWidth = width;
        windowHeight = height;
    }
}