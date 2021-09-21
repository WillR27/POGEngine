#include "POGGraphicsPCH.h"
#include "Drawing.h"

#include "POGGraphics/Graphics.h"
#include "POGGraphics/Mesh/Mesh.h"
#include "POGGraphics/Mesh/Primitives/Primitives.h"
#include "POGGraphics/Shader/Shader.h"

namespace POG::Graphics
{
	const char* vertexShader = R"(
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model * vec4(aPos, 1.0);
}
)";

	const char* fragmentShader = R"(
#version 330 core

out vec4 FragColor;

uniform vec3 colour;

void main()
{
	FragColor = vec4(1.0, 1.0, 0.0, 1.0);
} 
)";

	static Shader shader;
	Mesh mesh;

	void InitDrawing()
	{
		shader.Init(vertexShader, fragmentShader);

		mesh.SetNumberOfVerices(4);
		mesh.AddAttribute(Square::Positions, sizeof(Square::Positions), 3);
		mesh.SetIndexData(Square::Indices, sizeof(Square::Indices));
		mesh.Build();
	}

	void DrawRectangle(int x, int y, int width, int height, Maths::Vec3 colour)
	{
		shader.Use();
		shader.SetMatrix4fv("projection", 1, false, Maths::ToData(glm::ortho(0.0f, WindowWidth, 0.0f, WindowHeight)));
		shader.SetMatrix4fv("model", 1, false, Maths::ToData(Maths::ToModelMatrix(Maths::Vec3(x, y, 0.0f), Maths::Quat(), Maths::Vec3(width, height, 1.0f))));
		shader.Set3f("colour", colour.r, colour.g, colour.b);

		mesh.Render();
	}
}