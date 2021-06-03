#include "ExamplePCH.h"
#include "Example.h"

#include "POGCore/Main.h"

#include "POGCore.h"
#include "POGLog.h"
#include "POGRender.h"

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
		//mesh->SetPositionData(POG::Render::squarePositions, sizeof(POG::Render::squarePositions));
		//mesh->SetColourData(POG::Render::squareColours, sizeof(POG::Render::squareColours));
		//mesh->Build();

		material = std::make_shared<POG::Render::Material>();
		material->AddColour("colourIn", POG::Maths::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
		material->SetShader(meshShader);

		player = GetECSManager().CreateEntity();
		player.SetName("Player");
		player.AddComponent(POG::Core::AttachedCamera
			{
				.camera = POG::Render::Camera::MainCamera,
			});
		player.AddComponent(POG::Core::RigidBody
			{
				.force = POG::Maths::Vec3(0.0f, 0.0f, 0.0f),
				.velocity = POG::Maths::Vec3(0.0f, 0.0f, 0.0f),
				.mass = 1.0f,
				.dragCoef = 1.0f
			});
		player.AddComponent(POG::Core::Transform
			{
				.position = POG::Maths::Vec3(0.0f, 0.0f, -5.0f),
				.orientation = POG::Maths::Quat(POG::Maths::Vec3(0.0f, 0.0f, 0.0f)),
				.scale = POG::Maths::Vec3(1.0f, 1.0f, 1.0f),
			});

		square = GetECSManager().CreateEntity();
		square.SetName("Square");
		square.AddComponent(POG::Core::Transform
			{
				.position = POG::Maths::Vec3(0.0f, 0.0f, 0.0f),
				.orientation = POG::Maths::Quat(POG::Maths::Vec3(0.0f, 0.0f, 0.0f)),
				.scale = POG::Maths::Vec3(1.0f, 1.0f, 1.0f),
			});
		/*square.AddComponent(POG::Core::MeshRenderer
			{
				.mesh = mesh,
				.material = material,
			});*/
		square.AddComponent(POG::Core::Sprite
			{
				.texture = &squareTexture,
			});

		squareTexture.LoadFromImage("F:\\Dev\\Projects\\POGEngine\\Source\\Example\\Resources\\Sprites\\Blob.png");

		child = GetECSManager().CreateEntity();

	}

	void ExampleScene::Exit()
	{
	}

	void ExampleScene::Input(POG::Core::InputPackage& inputPackage, float dt)
	{
		POG::Core::Transform& squareTransform = square.GetComponent<POG::Core::Transform>();
		//squareTransform.orientation *= POG::Maths::Quat(POG::Maths::Vec3(0.0f, 0.0f, 1.0f * dt));

		POG::Core::RigidBody& playerRigidBody = player.GetComponent<POG::Core::RigidBody>();
		POG::Core::AttachedCamera& playerCamera = player.GetComponent<POG::Core::AttachedCamera>();

		float moveSpeed = 3.0f;
		playerRigidBody.velocity =
			(((playerCamera.camera->GetForwardVec() * static_cast<float>(inputPackage.GetAxisValue("Vertical"))) +
				(playerCamera.camera->GetRightVec() * static_cast<float>(inputPackage.GetAxisValue("Horizontal")))) +
				POG::Maths::Vec3(0.0f, static_cast<float>(inputPackage.GetAxisValue("Fly")), 0.0f)) * moveSpeed;

		if (inputPackage.HasMouseMoved())
		{
			float lookSpeed = 0.1f;
			playerCamera.camera->AddPitchAndYaw(POG::Core::Input::GetDeltaMouseY() * dt * lookSpeed, POG::Core::Input::GetDeltaMouseX() * dt * lookSpeed);
		}

		if (inputPackage.HasActionOccurred("Right") && !child.IsValid())
		{
			child = GetECSManager().CreateEntity();
			child.SetParent(square);

			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);
			GetECSManager().CreateEntity().SetParent(child);

			POG::Core::Entity child2 = GetECSManager().CreateEntity();
			child2.SetParent(child);

			GetECSManager().CreateEntity().SetParent(child2);
			GetECSManager().CreateEntity().SetParent(child2);
			GetECSManager().CreateEntity().SetParent(child2);
		}
		else if (inputPackage.HasActionOccurred("Left") && child.IsValid())
		{
			GetECSManager().DestroyEntity(child);
		}
	}

	void ExampleScene::Update(float dt)
	{
		GetPhysicsSystem().Update(dt);
		GetTransformSystem().Update(dt);
		GetCameraUpdateViewSystem().UpdateView();
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
		POG::Render::FaceCulling(false);
		POG::Render::CullFace(POG_BACK);
		POG::Render::DepthTest(true);
		POG::Render::Blend(true);

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
		GetSpriteRendererSystem().Frame(alpha);
	}


	ExampleApplication::ExampleApplication()
		: Application::Application("POG Example")
	{
	}

	void ExampleApplication::Init()
	{
		SetTargetUpdatesPerSecond(60.0f);
		SetTargetFramesPerSecond(60.0f);

		SetCursorEnabled(false);

		POG::Core::Scene::SetActiveScene(std::make_shared<ExampleScene>());

		GetInputManager().AddAction("Quit", POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_ESCAPE, POG_KEY_RELEASE, POG_MOD_ANY));
		GetInputManager().AddAction("Fullscreen", POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_F11, POG_KEY_RELEASE, POG_MOD_ANY));

		GetInputManager().AddAction("Left", POG::Core::InputInfo(POG::Core::InputType::Mouse, POG_MOUSE_BUTTON_LEFT, POG_KEY_RELEASE));
		GetInputManager().AddAction("Right", POG::Core::InputInfo(POG::Core::InputType::Mouse, POG_MOUSE_BUTTON_RIGHT, POG_KEY_RELEASE));

		GetInputManager().AddAxis("Fly",
			POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_LEFT_CONTROL, POG_KEY_PRESS),
			POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_LEFT_CONTROL, POG_KEY_RELEASE),
			POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_SPACE, POG_KEY_PRESS),
			POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_SPACE, POG_KEY_RELEASE));

		GetInputManager().AddAxis("Horizontal",
			POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_A, POG_KEY_PRESS),
			POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_A, POG_KEY_RELEASE),
			POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_D, POG_KEY_PRESS),
			POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_D, POG_KEY_RELEASE));
		
		GetInputManager().AddAxis("Vertical",
			POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_S, POG_KEY_PRESS),
			POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_S, POG_KEY_RELEASE),
			POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_W, POG_KEY_PRESS),
			POG::Core::InputInfo(POG::Core::InputType::Keyboard, POG_KEY_W, POG_KEY_RELEASE));
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
}

POG::Core::Application* POG::Core::CreateApplication()
{
	return new Example::ExampleApplication();
}