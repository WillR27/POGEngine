#include "pgpch.h"
#include "WorldScene.h"

#include "ECS/ECS.h"
#include "Render/Core/Render.h"
#include "Scene/Camera.h"

#include "Entities/Block.h"
#include "Entities/Player.h"

namespace Pagoog
{
	WorldScene::WorldScene()
		: Scene::Scene("World")
		//, meshSet()
	{
	}

	WorldScene::~WorldScene()
	{
	}

	void WorldScene::Init()
	{
		inputManager.AddAction("Left", InputInfo(InputType::Mouse, PG_MOUSE_BUTTON_LEFT, PG_KEY_RELEASE, PG_MOD_ANY));
		inputManager.AddAction("Right", InputInfo(InputType::Mouse, PG_MOUSE_BUTTON_RIGHT, PG_KEY_RELEASE, PG_MOD_ANY));

		inputManager.AddAction("Jump", InputInfo(InputType::Keyboard, PG_KEY_SPACE, PG_KEY_RELEASE, PG_MOD_ANY));

		inputManager.AddState("Sprint",
			InputInfo(InputType::Keyboard, PG_KEY_LEFT_SHIFT, PG_KEY_PRESS, PG_MOD_ANY),
			InputInfo(InputType::Keyboard, PG_KEY_LEFT_SHIFT, PG_KEY_RELEASE, PG_MOD_ANY));

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

		inputManager.AddInputCallback(PG_BIND_FN(InputCallback));

		meshRendererSystem = ecsManager.RegisterSystem<MeshRendererSystem>();

		Shared<Mesh> mesh = meshManager.CreateAndAddMesh("Mesh1");
		mesh->SetPositionData(squarePositions, sizeof(squarePositions));
		mesh->SetColourData(squareColours, sizeof(squareColours));
		mesh->Build();

		mesh = meshManager.CreateAndAddMesh("Mesh2");
		mesh->SetPositionData(cubePositions2, sizeof(cubePositions2));
		mesh->SetColourData(cubeColours2, sizeof(cubeColours2));
		mesh->Build();
		 
		mesh = meshManager.CreateAndAddMesh("Mesh3");
		mesh->SetPositionData(squarePositions2, sizeof(squarePositions2));
		mesh->SetColourData(squareColours2, sizeof(squareColours2));
		mesh->SetIndexData(squareIndices2, sizeof(squareIndices2));
		mesh->Build();

		mesh = meshManager.CreateAndAddMesh("Mesh4");
		mesh->SetPositionData(cubePositions3, sizeof(cubePositions3));
		mesh->SetColourData(cubeColours3, sizeof(cubeColours3));
		mesh->SetIndexData(cubeIndices3, sizeof(cubeIndices3));
		mesh->Build();

		//meshSet.Build();
		//meshSet.SetAttribute(0, 3, PG_FLOAT, false, 6 * sizeof(float), (void*)(0));
		//meshSet.SetAttribute(1, 3, PG_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));

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

		Shared<Shader> shader = shaderManager.CreateAndAddShader("Shader1");
		shader->Init(vertexShaderSource, fragmentShaderSource);

		Shared<Material> material = materialManager.CreateAndAddMaterial("Material1");
		material->AddColour("colourIn", Vec4(1.0f, 0.0f, 0.0f, 1.0f));
		material->SetShader(shaderManager.FindShader("Shader1"));

		// Create a player
		player = ecsManager.CreateEntity<Player>(10.0f, 3.0f, 0.2f);
		inputManager.AddInputCallback(PG_BIND_FN(player.InputCallback));

		// Set the main camera
		Camera::MainCamera = player.GetComponent<ECSCamera>().camera;
	}

	void WorldScene::Update(float dt)
	{
	}

	void WorldScene::FrameUpdate(float alpha)
	{
		Render::SetPolygonMode(PG_FRONT_AND_BACK, PG_FILL);
		Render::EnableDepthTest(true);

		meshRendererSystem->FrameUpdate(alpha);
	}

	void WorldScene::HandleEvent(Event& e)
	{
	}

	void WorldScene::InputCallback(InputPackage& inputPackage, float dt)
	{
		if (inputPackage.HasActionOccurred("Right"))
		{
			Block block = ecsManager.CreateEntity<Block>();
			
			block.GetComponent<ECSTransform>().position = player.GetComponent<ECSTransform>().position;
			block.GetComponent<ECSTransform>().prevPosition = player.GetComponent<ECSTransform>().prevPosition;
			block.GetComponent<ECSMeshRenderer>().mesh = meshManager.FindMesh("Mesh4");
			block.GetComponent<ECSMeshRenderer>().material = materialManager.FindMaterial("Material1");
		}
	}
}