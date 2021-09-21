#include "POGCorePCH.h"
#include "PanelControl.h"

#include "POGCore/Graphics/MeshManager.h"

#include "POGGraphics.h"

namespace POG::Core
{
	PanelControl::PanelControl()
		: Control::Control()
		, colour(1.0f, 1.0f, 1.0f)
	{
	}

	void PanelControl::Draw()
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

		Graphics::Disable(Graphics::Capability::DepthTest);

		Graphics::Shader shader;
		shader.Init(vertexShader, fragmentShader);

		x = 100;
		y = 100;

		width = 600;
		height = 400;

		/*shader.Use();
		shader.SetMatrix4fv("projection", 1, false, Maths::ToData(glm::ortho(0.0f, 1200.0f, 0.0f, 800.0f)));
		shader.SetMatrix4fv("model", 1, false, Maths::ToData(Maths::ToModelMatrix(Maths::Vec3(x + (width / 2.0f), (800.0f - y) - (height / 2.0f), 0.0f), Maths::Quat(), Maths::Vec3(width, height, 1.0f))));
		shader.Set3f("colour", colour.r, colour.g, colour.b);

		Graphics::Mesh& mesh = MeshManager::GetDefaultMesh("Square Mesh");
		mesh.Render();*/

		Graphics::DrawRectangle(x + (width / 2), (800 - y) - (height / 2), width, height, colour);

		Graphics::Enable(Graphics::Capability::DepthTest);
	}
}