#include "pgpch.h"
#include "ECSLayer.h"

#include "Core/Time.h"
#include "Input/Input.h"
#include "Render/Mesh/StaticMeshSet.h"
#include "Render/Mesh/Primitives/Primitives.h"

namespace Pagoog
{
	ECSLayer::ECSLayer()
		: Layer::Layer("ECS")
		, meshSet()
		, mesh(&meshSet)
		, mesh2(&meshSet)
		, mesh3(&meshSet)
		, mesh4(&meshSet)
		, material1("Material1")
	{
	}

	ECSLayer::~ECSLayer()
	{
	}

	void ECSLayer::Init()
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



		/*std::vector<Entity> entities(20);

		for (Entity& entity : entities)
		{
			entity = coordinator.CreateEntity();

			coordinator.AddComponent(entity, ECSTransform
				{
					.position = Vec3(0.0f, 0.0f, 0.0f),
					.orientation = Quat(Vec3(0.0f, 0.0f, 0.0f)),
					.scale = Vec3(1.0f, 1.0f, 1.0f)
				});

			coordinator.AddComponent(entity, ECSRigidBody
				{
					.force = Vec3(0.0f, 0.0f, 0.0f),
					.velocity = Vec3(0.0f, 0.0f, 0.0f),
					.mass = 1.0f,
					.dragCoef = 1.0f
				});

			coordinator.AddComponent(entity, ECSBoxCollider
				{
					.aabb = AABB<3>({ 2.0f, 2.0f, 2.0f }),
					.stickiness = 0.5f
				});

			coordinator.AddComponent(entity, ECSMeshRenderer
				{
					.mesh = &mesh4,
					.material = &material1
				});
		}*/



		player = coordinator.CreateEntity();

		coordinator.AddComponent(player, ECSTransform
			{
				.position = Vec3(0.0f, 0.0f, 0.0f),
				.orientation = Quat(Vec3(0.0f, 0.0f, 0.0f)),
				.scale = Vec3(1.0f, 1.0f, 1.0f)
			});

		coordinator.AddComponent(player, ECSRigidBody
			{
				.force = Vec3(0.0f, 0.0f, 0.0f),
				.velocity = Vec3(0.0f, 0.0f, 0.0f),
				.mass = 1.0f,
				.dragCoef = 1.0f
			});

		coordinator.AddComponent(player, ECSBoxCollider
			{
				.aabb = AABB<3>({ 2.0f, 2.0f, 2.0f }),
				.stickiness = 0.5f
			});



		player2 = Scene::CreateGameObject<Player>();
		Transform& transform = *player2->GetComponent<Transform>();
		transform.SetPosition(Vec3(0.0f, 0.0f, 10.0f));
		Camera* camera = player2->GetComponent<Camera>();
		Camera::MainCamera = camera;
		inputManager.AddInputPackageCallback(PG_BIND_FN(player2->ActionCallback));
	}

	void ECSLayer::CollisionsUpdate(float dt)
	{
	}

	void ECSLayer::Update(float dt)
	{
		//PG_TRACE(coordinator.GetComponent<ECSTransform>(0).position.ToString());
	}

	void ECSLayer::FrameUpdate(float alpha)
	{
		Render::SetPolygonMode(PG_FRONT_AND_BACK, PG_FILL);
		Render::EnableDepthTest(true);
	}

	void ECSLayer::HandleEvent(Event& e)
	{
	}

	void ECSLayer::ActionCallback(InputPackage& inputPackage, float dt)
	{
		if (inputPackage.HasActionOccurred("Right"))
		{
			Entity entity = coordinator.CreateEntity();

			coordinator.AddComponent(entity, ECSTransform
				{
					.position = player2->GetComponent<Transform>()->GetPosition(),
					.orientation = Quat(Vec3(0.0f, 0.0f, 0.0f)),
					.scale = Vec3(1.0f, 1.0f, 1.0f)
				});

			coordinator.AddComponent(entity, ECSRigidBody
				{
					.force = Vec3(0.0f, 0.0f, 0.0f),
					.velocity = Vec3(0.0f, 0.0f, 0.0f),
					.mass = 1.0f,
					.dragCoef = 1.0f
				});

			coordinator.AddComponent(entity, ECSBoxCollider
				{
					.aabb = AABB<3>({ 2.0f, 2.0f, 2.0f }),
					.stickiness = 0.5f
				});

			coordinator.AddComponent(entity, ECSMeshRenderer
				{
					.mesh = &mesh4,
					.material = &material1
				});
		}
	}
}