#include "pgpch.h"
#include "WorldLayer.h"

#include "Core/Time.h"
#include "Game/Camera.h"
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
		, blockTemplate()
		, controllableBlock(nullptr)
	{
	}

	WorldLayer::~WorldLayer()
	{
	}

	void WorldLayer::Init()
	{
		inputManager.AddAction("Jump", InputInfo(PG_KEY_SPACE, PG_KEY_RELEASE, PG_MOD_NONE));
		//inputManager.AddState("Forwards", InputInfo(PG_KEY_W, PG_KEY_PRESS, PG_MOD_NONE), InputInfo(PG_KEY_W, PG_KEY_RELEASE, PG_MOD_NONE));
		//inputManager.AddState("Backwards", InputInfo(PG_KEY_S, PG_KEY_PRESS, PG_MOD_NONE), InputInfo(PG_KEY_S, PG_KEY_RELEASE, PG_MOD_NONE));
		//inputManager.AddState("Left", InputInfo(PG_KEY_A, PG_KEY_PRESS, PG_MOD_NONE), InputInfo(PG_KEY_A, PG_KEY_RELEASE, PG_MOD_NONE));
		//inputManager.AddState("Right", InputInfo(PG_KEY_D, PG_KEY_PRESS, PG_MOD_NONE), InputInfo(PG_KEY_D, PG_KEY_RELEASE, PG_MOD_NONE));
		inputManager.AddAxis("Horizontal", InputInfo(PG_KEY_A, PG_KEY_PRESS, PG_MOD_NONE), InputInfo(PG_KEY_A, PG_KEY_RELEASE, PG_MOD_NONE), InputInfo(PG_KEY_D, PG_KEY_PRESS, PG_MOD_NONE), InputInfo(PG_KEY_D, PG_KEY_RELEASE, PG_MOD_NONE));
		inputManager.AddAxis("Vertical", InputInfo(PG_KEY_S, PG_KEY_PRESS, PG_MOD_NONE), InputInfo(PG_KEY_S, PG_KEY_RELEASE, PG_MOD_NONE), InputInfo(PG_KEY_W, PG_KEY_PRESS, PG_MOD_NONE), InputInfo(PG_KEY_W, PG_KEY_RELEASE, PG_MOD_NONE));
		inputManager.AddInputPackageCallback(PG_BIND_FN(ActionCallback));

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

		Camera camera(Vec3(0.0f, 0.0f, 10.0f));
		material1.GetShader().Use();
		material1.GetShader().SetMatrix4fv("view", 1, false, camera.GetView());
		material1.GetShader().SetMatrix4fv("projection", 1, false, camera.GetProjection());

		material1.SetColour("colourIn", Vec4((float)(sin(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) + 1.0f) / 2.0f, (float)(sin(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) * 0.9f) + 1.0f) / 2.0f, (float)(sin(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) * 1.1f) + 1.0f) / 2.0f, 1.0f));

		blockTemplate.SetMaterial(material1);
		blockTemplate.SetMesh(mesh4);

		controllableBlock = Scene::CreateGameObject(blockTemplate);
		controllableBlock->SetPosition(Vec3(-2.5f, 0.0f, 0.0f));
		//controllableBlock->SetForce(Vec3(0.01f, 0.0f, 0.0f));

		Block* staticBlock = Scene::CreateGameObject(blockTemplate);
		staticBlock->SetPosition(Vec3(0.0f, 0.0f, 0.0f));
	}

	void WorldLayer::Update(float dt)
	{

	}

	void WorldLayer::FrameUpdate(float dt)
	{
		Render::SetPolygonMode(PG_FRONT_AND_BACK, PG_FILL);
		Render::EnableDepthTest(true);

		//float rand1 = (std::rand() % 100) / 100.0f;
		//float rand2 = (std::rand() % 100) / 100.0f;
		//float rand3 = (std::rand() % 100) / 100.0f;
		//block.RotateAround(Vec3(rand1 / 1.f, rand2 / 1.f, rand3 / 1.f), Quaternion(Vec3(rand1 / 1000.f, rand2 / 1000.f, rand3 / 1000.f)));
		//block.Rotate(Quaternion(Vec3(rand1 / 1000.f, rand2 / 1000.f, rand3 / 1000.f)));
	}

	void WorldLayer::HandleEvent(Event& e)
	{
		EventDispatcher ed(e);
		ed.Dispatch<KeyEvent>(PG_BIND_FN(inputManager.HandleKeyEvent));
	}

	void WorldLayer::ActionCallback(InputPackage& inputPackage, float dt)
	{
		if (inputPackage.HasActionOccurred("Jump"))
		{
			controllableBlock->Rotate(Quat(Vec3(0.5f, 0.3f, 0.7f)));
		}

		controllableBlock->SetVelocity(Vec3(inputPackage.GetAxisValue("Horizontal") / 4.0f, 0.0f, -inputPackage.GetAxisValue("Vertical") / 4.0f));
	}
}