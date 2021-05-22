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

		meshShader = std::make_shared<POG::Render::Shader>();
		vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//uniform vec4 colourIn;

out vec3 colour;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
	//gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	colour = aColour;
	//colour = vec3(colourIn.r, colourIn.g, colourIn.b);
}
)";

		fragmentShaderSource = R"(
#version 330 core
in vec3 colour;

out vec4 FragColor;

void main()
{
	//FragColor = vec4(0.0f, 0.2f, 0.9f, 1.0f);
    FragColor = vec4(colour, 1.0);
} 
)";

		meshShader->Init(vertexShaderSource, fragmentShaderSource);

		mesh = std::make_shared <POG::Render::Mesh>();
		mesh->SetPositionData(POG::Render::squarePositions, sizeof(POG::Render::squarePositions));
		mesh->SetColourData(POG::Render::squareColours, sizeof(POG::Render::squareColours));
		mesh->Build();

		material = std::make_shared<POG::Render::Material>();
		material->AddColour("colourIn", POG::Maths::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
		material->SetShader(meshShader);

		POG::Core::Entity entity = GetECSManager().CreateEntity();
		entity.AddComponent<POG::Core::Transform>(POG::Core::Transform
			{
				.position = POG::Maths::Vec3(0.0f, 0.0f, 0.0f),
				.orientation = POG::Maths::Quat(POG::Maths::Vec3(0.0f, 0.0f, 0.0f)),
				.scale = POG::Maths::Vec3(1.0f, 1.0f, 1.0f),
			});
		entity.AddComponent<POG::Core::MeshRenderer>(POG::Core::MeshRenderer
			{
				.mesh = mesh,
				.material = material,
			});
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
		GetTransformSystem().Update(dt);
	}

	void ExampleScene::Frame(float alpha)
	{
		float r = ((float)rand() / (RAND_MAX)) / 3.0f + 0;
		float g = ((float)rand() / (RAND_MAX)) / 3.0f + 0;
		float b = ((float)rand() / (RAND_MAX)) / 3.0f + 0;

		POG::Render::ClearColour(r, g, b, 1.0f);
		POG::Render::ClearColourBuffer();
		POG::Render::ClearDepthBuffer();
	
		POG::Render::SetPolygonMode(POG_FRONT_AND_BACK, POG_FILL);
		POG::Render::SetFrontFace(POG_CW);
		POG::Render::FaceCulling(true);
		POG::Render::CullFace(POG_BACK);
		POG::Render::DepthTest(true);

		POG::Render::Camera::MainCamera->UpdateView(POG::Maths::Vec3(0.0f, 0.0f, -10.0f), POG::Maths::Quat(POG::Maths::Vec3(0.5f, 0.0f, 0.0f)));

		//if (flip)
		//{
		//	float vertices[] =
		//	{
		//		0.5f, 0.5f, 0.0f,
		//		-0.5f, 0.5f, 0.0f,
		//		-0.0f, -0.5f, 0.0f
		//	};

		//	vbo.Bind();
		//	vbo.SetVertexData(vertices, sizeof(vertices));
		//}
		//else
		//{
		//	float vertices[] =
		//	{
		//		-0.5f, -0.5f, 0.0f,
		//		0.5f, -0.5f, 0.0f,
		//		0.0f,  0.5f, 0.0f
		//	};

		//	vbo.Bind();
		//	vbo.SetVertexData(vertices, sizeof(vertices));
		//}

		//vao.Bind();
		//vao.SetAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		//shader.Use();

		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//meshShader->Use();
		//mesh->Render();

		GetMeshRendererSystem().Frame(alpha);
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

		inputManager.AddAction("Quit", POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_ESCAPE, POG_KEY_RELEASE, POG_MOD_ANY));
		inputManager.AddAction("Fullscreen", POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_F11, POG_KEY_RELEASE, POG_MOD_ANY));
		inputManager.AddAction("Jump", POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_SPACE, POG_KEY_RELEASE, POG_MOD_CONTROL));
			
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