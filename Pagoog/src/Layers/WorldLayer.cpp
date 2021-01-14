#include "pgpch.h"
#include "WorldLayer.h"

#include "Core/Time.h"
#include "Game/GameObject/Components/Camera.h"
#include "Input/Input.h"
#include "Render/Mesh/StaticMeshSet.h"
#include "Render/Mesh/Primitives/Primitives.h"
#include "Scene/Scene.h"

namespace Pagoog
{
	WorldLayer::WorldLayer()
		: Layer::Layer("World")
		, meshSet()
		, mesh(&meshSet)
		, mesh2(&meshSet)
		, mesh3(&meshSet)
		, mesh4(&meshSet)
		, material1("Material1")
		, templateBlock()
		, controllableBlock(nullptr)
		, player(nullptr)
	{
	}

	WorldLayer::~WorldLayer()
	{
	}

	void WorldLayer::Init()
	{
		inputManager.AddAction("Left", InputInfo(InputType::Mouse, PG_MOUSE_BUTTON_LEFT, PG_KEY_RELEASE, PG_MOD_ANY));
		inputManager.AddAction("Right", InputInfo(InputType::Mouse, PG_MOUSE_BUTTON_RIGHT, PG_KEY_RELEASE, PG_MOD_ANY));
		
		inputManager.AddAction("Jump", InputInfo(InputType::Keyboard, PG_KEY_SPACE, PG_KEY_RELEASE, PG_MOD_ANY));
		
		inputManager.AddAxis("Fly", 
			InputInfo(InputType::Keyboard, PG_KEY_LEFT_CONTROL, PG_KEY_PRESS, PG_MOD_ANY), 
			InputInfo(InputType::Keyboard, PG_KEY_LEFT_CONTROL, PG_KEY_RELEASE, PG_MOD_ANY), 
			InputInfo(InputType::Keyboard, PG_KEY_SPACE, PG_KEY_PRESS, PG_MOD_ANY), 
			InputInfo(InputType::Keyboard, PG_KEY_SPACE, PG_KEY_RELEASE, PG_MOD_ANY));
		
		inputManager.AddAxis("Horizontal", 
			InputInfo(InputType::Keyboard, PG_KEY_A, PG_KEY_PRESS, PG_MOD_ANY), 
			InputInfo(InputType::Keyboard, PG_KEY_A, PG_KEY_RELEASE, PG_MOD_ANY), 
			InputInfo(InputType::Keyboard, PG_KEY_D, PG_KEY_PRESS, PG_MOD_ANY), 
			InputInfo(InputType::Keyboard, PG_KEY_D, PG_KEY_RELEASE, PG_MOD_ANY));
		
		inputManager.AddAxis("Vertical", 
			InputInfo(InputType::Keyboard, PG_KEY_S, PG_KEY_PRESS, PG_MOD_ANY), 
			InputInfo(InputType::Keyboard, PG_KEY_S, PG_KEY_RELEASE, PG_MOD_ANY), 
			InputInfo(InputType::Keyboard, PG_KEY_W, PG_KEY_PRESS, PG_MOD_ANY), 
			InputInfo(InputType::Keyboard, PG_KEY_W, PG_KEY_RELEASE, PG_MOD_ANY));
		
		inputManager.AddInputPackageCallback(PG_BIND_FN(ActionCallback));
		inputManager.AddInputPackageCallback(PG_BIND_FN(player->ActionCallback));

		mesh.SetPositionData(squarePositions, sizeof(squarePositions));
		mesh.SetColourData(squareColours, sizeof(squareColours));
		mesh.Build();

		mesh2.SetPositionData(cubePositions2, sizeof(cubePositions2));
		mesh2.SetColourData(cubeColours2, sizeof(cubeColours2));
		mesh2.Build();

		mesh3.SetPositionData(squarePositions2, sizeof(squarePositions2));
		mesh3.SetColourData(squareColours2, sizeof(squareColours2));
		mesh3.SetIndexData(squareIndices2, sizeof(squareIndices2));
		mesh3.Build();

		mesh4.SetPositionData(cubePositions3, sizeof(cubePositions3));
		mesh4.SetColourData(cubeColours3, sizeof(cubeColours3));
		mesh4.SetIndexData(cubeIndices3, sizeof(cubeIndices3));
		mesh4.Build();

		meshSet.Build();
		meshSet.SetAttribute(0, 3, PG_FLOAT, false, 6 * sizeof(float), (void*)(0));
		meshSet.SetAttribute(1, 3, PG_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 colourIn;

out vec3 colour;

void main()
{
	//colour = vec3(colourIn.r, colourIn.g, colourIn.b);
	colour = aColour;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

		const char* fragmentShaderSource = R"(
#version 330 core
in vec3 colour;

out vec4 FragColor;

void main()
{
    FragColor = vec4(colour, 1.0);
} 
)";

		shader.Init(vertexShaderSource, fragmentShaderSource);

		material1.AddColour("colourIn", Vec4(1.0f, 0.0f, 0.0f, 1.0f));
		material1.SetShader(shader);

		material1.SetColour("colourIn", Vec4((float)(sin(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) + 1.0f) / 2.0f, (float)(sin(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) * 0.9f) + 1.0f) / 2.0f, (float)(sin(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) * 1.1f) + 1.0f) / 2.0f, 1.0f));

		templateBlock.GetComponent<MeshRenderer>()->SetMaterial(material1);
		templateBlock.GetComponent<MeshRenderer>()->SetMesh(mesh4);

		controllableBlock = Scene::AddGameObject(templateBlock);
		controllableBlock->GetComponent<Transform>()->SetPosition(Vec3(-4.0f, 0.0f, 0.0f));
		controllableBlock->GetComponent<RigidBody>()->SetMass(0.5f);

		templateBlock.SetName("111111111");
		Block* staticBlock = Scene::AddGameObject(templateBlock);
		staticBlock->GetComponent<Transform>()->SetPosition(Vec3(0.0f, 0.0f, 0.0f));
		staticBlock->GetComponent<RigidBody>()->SetDragCoef(3.0f);

		templateBlock.SetName("2222222222");
		staticBlock = Scene::AddGameObject(templateBlock);
		staticBlock->GetComponent<Transform>()->SetPosition(Vec3(-10.0f, 1.0f, 10.0f));
		staticBlock->GetComponent<RigidBody>()->SetDragCoef(3.0f);

		templateBlock.SetName("333333333");
		staticBlock = Scene::AddGameObject(templateBlock);
		staticBlock->GetComponent<Transform>()->SetPosition(Vec3(10.0f, -1.0f, 10.0f));
		staticBlock->GetComponent<RigidBody>()->SetDragCoef(3.0f);

		templateBlock.SetName("444444444");
		staticBlock = Scene::AddGameObject(templateBlock);
		staticBlock->GetComponent<Transform>()->SetPosition(Vec3(00.0f, 1.0f, 20.0f));
		staticBlock->GetComponent<RigidBody>()->SetDragCoef(3.0f);

		player = Scene::CreateGameObject<Player>();
		player->GetComponent<MeshRenderer>()->SetMaterial(material1);
		//player->GetComponent<MeshRenderer>()->SetMesh(mesh2);
		Transform& transform = *player->GetComponent<Transform>();
		transform.SetPosition(Vec3(0.0f, 0.0f, 10.0f));

		Camera* camera = player->GetComponent<Camera>();
		Camera::MainCamera = camera;
	}

	void WorldLayer::CollisionsUpdate(float dt)
	{
	}

	void WorldLayer::Update(float dt)
	{
		if (Scene::IsInScene(controllableBlock))
		{
			controllableBlock->GetComponent<Transform>()->Rotate(Quat(Vec3(0.002f, 0.001f, 0.003f)));
		}
	}

	void WorldLayer::FrameUpdate(float alpha)
	{
		Render::SetPolygonMode(PG_FRONT_AND_BACK, PG_FILL);
		Render::EnableDepthTest(true);
	}

	void WorldLayer::HandleEvent(Event& e)
	{
		
	}

	void WorldLayer::ActionCallback(InputPackage& inputPackage, float dt)
	{
		if (inputPackage.HasActionOccurred("Jump"))
		{
			if (Scene::IsInScene(controllableBlock))
			{
				controllableBlock->GetComponent<Transform>()->Rotate(Quat(Vec3(0.2f, 0.1f, 0.3f)));
			}
		}

		if (inputPackage.HasActionOccurred("Right"))
		{
			Block* block = Scene::AddGameObject(templateBlock);
			block->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());
		}
	}
}