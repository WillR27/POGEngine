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
    FT_Library ft;

    std::map<const char*, std::map<char, Character>> Fonts;

	void InitText()
	{
        if (int error = FT_Init_FreeType(&ft))
        {
            POG_ERROR("Failed to initialise FreeType with error code: {0}", error);
        }

        LoadFont("Arial", "F:\\arial.ttf");
	}

    void LoadFont(const char* name, const char* file)
    {
        FT_Face face;
        if (int error = FT_New_Face(ft, file, 0, &face))
        {
            POG_ERROR("Failed to load font with error code: {0}", error);
        }

        FT_Set_Pixel_Sizes(face, 0, 48);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

        auto& chars = Fonts[name];
        for (unsigned char c = 0; c < 128; c++)
        {
            // load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                POG_ERROR("EGGG");
                continue;
            }

            Texture* texture2 = new Texture();
            texture2->SetDataRed(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows);
            Character character
            {
                texture2,
                Maths::Vec2i(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                Maths::Vec2i(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x,
            };
            chars.insert({ c, character });
        }

        FT_Done_Face(face);
        //FT_Done_FreeType(ft);
    }

	void RenderText(std::string text, float x, float y, float scale, Maths::Vec3 colour)
	{
		VertexArray vao;
		VertexBuffer vbo;
		vao.Bind();
		vbo.Bind();
		vbo.SetVertexData(nullptr, sizeof(float) * 6 * 4);
		vao.SetAttribute(0, 4, POG_FLOAT, false, 4 * sizeof(float), 0);

        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        float vertices[6][4] = {
    { 1,     1,   0.0f, 0.0f },
    { 1,     1,       0.0f, 1.0f },
    { 1, 1,       1.0f, 1.0f },

    { 10,     1,   0.0f, 0.0f },
    { 12, 66,       1.0f, 1.0f },
    { 1, 56,   1.0f, 0.0f }
        };

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

        glm::mat4 projection = glm::ortho(0.0f, 1200.0f, 0.0f, 800.0f);

		Shader shader;
		shader.Init(textVertexShader, textFragmentShader);
        shader.Use();
		shader.SetMatrix4fv("projection", 1, false, Maths::ToData(projection));
		shader.Set3f("textColor", colour.r, colour.g, colour.b);

        vao.Bind();

        Disable(Graphics::Capability::DepthTest);

        auto& Characters = Fonts["Arial"];

        for (auto c = text.begin(); c != text.end(); c++)
        {
            Character ch = Characters[*c];

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

            ch.texture->Bind();
            vbo.Bind();
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

            RenderTrianglesFromArrays(0, 6);

            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }

        Enable(Graphics::Capability::DepthTest);
	}
}