#include "ExamplePCH.h"
#include "Example.h"

#include "POGCore.h"
#include "POGRender.h"

#include "POGCore/Main.h"

#include <glad/glad.h>

namespace Example
{
	void ExampleScene::Init()
	{
		const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

		const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

		shader.Init(vertexShaderSource, fragmentShaderSource);
	}

	void ExampleScene::Exit()
	{
	}

	void ExampleScene::Update(float dt)
	{

	}

	void ExampleScene::FrameUpdate(float alpha)
	{
		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.0f,  0.5f, 0.0f
		};

		vbo.Bind();
		vbo.SetVertexData(vertices, sizeof(vertices));

		vao.Bind();
		vao.SetAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		shader.Use();

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void ExampleScene::HandleEvent(POG::Core::Event& e)
	{

	}

	ExampleApplication::ExampleApplication()
		: Application::Application("POG Example")
	{
	}

	void ExampleApplication::Init()
	{
		inputManager.AddAction("Quit", POG::Core::InputInfo(POG::Core::InputType::Keyboard, PG_KEY_ESCAPE, PG_KEY_RELEASE, PG_MOD_ANY));
		inputManager.AddAction("Fullscreen", POG::Core::InputInfo(POG::Core::InputType::Keyboard, PG_KEY_F11, PG_KEY_RELEASE, PG_MOD_ANY));
			
		activeScene = std::make_unique<ExampleScene>();
	}

	void ExampleApplication::Input(POG::Core::InputPackage& inputPackage, float dt)
	{
		if (inputPackage.HasActionOccurred("Quit", true))
		{
			Quit();
		}

		if (inputPackage.HasActionOccurred("Fullscreen", true))
		{
			GetWindow().ToggleFullscreen();
		}
	}
}

#ifdef POG_STANDALONE

std::unique_ptr<POG::Core::Application> POG::Core::CreateApplication()
{
	return std::make_unique<Example::ExampleApplication>();
}

#endif