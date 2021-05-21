#include "ExamplePCH.h"
#include "Example.h"

#include "POGCore.h"
#include "POGLog.h"
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
FragColor = vec4(0.0f, 0.2f, 0.9f, 1.0f);
}
)";

		shader.Init(vertexShaderSource, fragmentShaderSource);
	}

	void ExampleScene::Exit()
	{
	}

	void ExampleScene::Input(POG::Core::InputPackage& inputPackage, float dt)
	{
		if (inputPackage.HasActionOccurred("Jump"))
		{
			flip = !flip;
		}
	}

	void ExampleScene::Update(float dt)
	{

	}

	void ExampleScene::Frame(float alpha)
	{
		float r = ((float)rand() / (RAND_MAX)) / 3.0f + 0;
		float g = ((float)rand() / (RAND_MAX)) / 3.0f + 0;
		float b = ((float)rand() / (RAND_MAX)) / 3.0f + 0;

		POG::Render::ClearColour(r, g, b, 1.0f);
		POG::Render::ClearColourBuffer();
		POG::Render::ClearDepthBuffer();
		 
		if (flip)
		{
			float vertices[] =
			{
				0.5f, 0.5f, 0.0f,
				-0.5f, 0.5f, 0.0f,
				-0.0f, -0.5f, 0.0f
			};

			vbo.Bind();
			vbo.SetVertexData(vertices, sizeof(vertices));
		}
		else
		{
			float vertices[] =
			{
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.0f,  0.5f, 0.0f
			};

			vbo.Bind();
			vbo.SetVertexData(vertices, sizeof(vertices));
		}

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
		SetTargetUpdatesPerSecond(60.0f);
		SetTargetFramesPerSecond(60.0f);

		inputManager.AddAction("Fullscreen", POG::Core::InputInfo(POG::Core::InputType::Keyboard, PG_KEY_F11, PG_KEY_RELEASE, PG_MOD_ANY));
		inputManager.AddAction("Jump", POG::Core::InputInfo(POG::Core::InputType::Keyboard, PG_KEY_SPACE, PG_KEY_RELEASE, PG_MOD_CONTROL));
			
		activeScene = std::make_unique<ExampleScene>();
	}

	void ExampleApplication::TryUpdate(float timeBetweenLoops)
	{
		Application::TryUpdate(timeBetweenLoops);
	}

	void ExampleApplication::TryFrame(float timeBetweenLoops)
	{
		Application::TryFrame(timeBetweenLoops);
	}

	void ExampleApplication::Input(POG::Core::InputPackage& inputPackage, float dt)
	{
		if (inputPackage.HasActionOccurred("Quit", true))
		{
			Exit();
		}

		if (inputPackage.HasActionOccurred("Fullscreen", true))
		{
			ToggleFullscreen();
		}
	}

	void ExampleApplication::Update(float dt)
	{
		Application::Update(dt);
	}

	void ExampleApplication::Frame(float alpha)
	{
		Application::Frame(alpha);
	}

	void ExampleApplication::HandleEvent(POG::Core::Event& e)
	{
		Application::HandleEvent(e);
	}
}

POG::Core::Application* POG::Core::CreateApplication()
{
	return new Example::ExampleApplication();
}