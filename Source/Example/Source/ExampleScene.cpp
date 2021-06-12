#include "ExamplePCH.h"
#include "ExampleScene.h"

using namespace POG;

namespace Example
{
	void ExampleScene::Init()
	{
		Graphics::Texture& blobTexture = Core::TextureManager::CreateGlobalTexture("Blob");
		blobTexture.LoadFromImage("Resources\\Sprites\\Rectangle.png");

		player = GetECSManager().CreateEntity();
		player.SetName("Player");
		player.AddComponent(Core::AttachedCamera
			{
				.camera = Core::Camera::MainCamera,
			});
		player.AddComponent(Core::RigidBody
			{
				.force = Maths::Vec3(0.0f, 0.0f, 0.0f),
				.velocity = Maths::Vec3(0.0f, 0.0f, 0.0f),
				.mass = 1.0f,
				.dragCoef = 1.0f
			});
		player.AddComponent(Core::Transform
			{
				.position = Maths::Vec3(0.0f, 0.0f, -2.0f),
				.orientation = Maths::Quat(Maths::Vec3(0.0f, 0.0f, 0.0f)),
				.scale = Maths::Vec3(1.0f, 1.0f, 1.0f),
			});

		square = GetECSManager().CreateEntity();
		square.SetName("Square");
		square.AddComponent(Core::Transform
			{
				.position = Maths::Vec3(1.0f, -1.2f, 1.1f),
				.orientation = Maths::Quat(Maths::Vec3(0.0f, 0.0f, 0.0f)),
				.scale = Maths::Vec3(1.5f, 1.0f, 1.0f),
			});
		square.AddComponent(Core::RectCollider
			{
				.min = Maths::Vec2(-0.5f, -0.5f),
				.max = Maths::Vec2(0.5f, 0.5f),
			});
		/*square.AddComponent(Core::MeshRenderer
			{
				.mesh = mesh,
				.material = material,
			});*/
		square.AddComponent(Core::Sprite
			{
				.texture = &blobTexture,
				.pixelsToUnitsRatio = 100.0f,
			});

		child = GetECSManager().CreateEntity();
	}

	void ExampleScene::Exit()
	{
	}

	void ExampleScene::Input(Core::InputPackage& inputPackage, float dt)
	{
		Core::Transform& squareTransform = square.GetComponent<Core::Transform>();
		Core::RectCollider& squareRectCollider = square.GetComponent<Core::RectCollider>();
		Core::Sprite& squareSprite = square.GetComponent<Core::Sprite>();

		Core::Transform& playerTransform = player.GetComponent<Core::Transform>();
		Core::RigidBody& playerRigidBody = player.GetComponent<Core::RigidBody>();
		Core::AttachedCamera& playerCamera = player.GetComponent<Core::AttachedCamera>();

		float moveSpeed = 3.0f;
		playerRigidBody.velocity =
			(((playerCamera.camera->GetForwardVec() * static_cast<float>(inputPackage.GetAxisValue("Vertical"))) +
				(playerCamera.camera->GetRightVec() * static_cast<float>(inputPackage.GetAxisValue("Horizontal")))) +
				Maths::Vec3(0.0f, static_cast<float>(inputPackage.GetAxisValue("Fly")), 0.0f)) * moveSpeed;

		if (inputPackage.HasMouseMoved())
		{
			float lookSpeed = 0.1f;
			//playerCamera.camera->AddPitchAndYaw(Core::Input::GetDeltaMouseY() * dt * lookSpeed, Core::Input::GetDeltaMouseX() * dt * lookSpeed);

			//auto& sprite = square.GetComponent<Core::Sprite>();

			//Core::TextureManager::DestroyGlobalTexture("Blob");
			//Graphics::Texture& blobTexture = Core::TextureManager::CreateGlobalTexture("Bloboid");
			//blobTexture.LoadFromImage("Resources\\Sprites\\Blob.png");

			//sprite.texture = &blobTexture;
		}

		if (inputPackage.HasActionOccurred("Left"))
		{
			Core::Ray ray = Core::CalcMouseRay(playerTransform.position);
			Core::RayResultRectCollider result = Core::Hits(ray, squareTransform, squareRectCollider, squareSprite);
			if (result.hit)
			{
				POG_TRACE("{0}, {1}, {2}", result.pointOfIntersection.x, result.pointOfIntersection.y, result.pointOfIntersection.z);
				POG_WARN("{0}, {1}", result.pointOnRect.x, result.pointOnRect.y);
			}
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

			Core::Entity child2 = GetECSManager().CreateEntity();
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
		Core::Transform& squareTransform = square.GetComponent<Core::Transform>();
		Core::RectCollider& squareRectCollider = square.GetComponent<Core::RectCollider>();

		if (Core::Input::MouseButtonReleased(POG_MOUSE_BUTTON_LEFT))
		{
			POG_TRACE("asdsad");
		}

		// No idea what normalising needs doing
		squareTransform.orientation *= Maths::Quat(Maths::Vec3(0.5f * dt, 0.5f * dt, 0.5f * dt));
		squareTransform.orientation = Maths::Normalise(squareTransform.orientation);

		Core::Transform& playerTransform = player.GetComponent<Core::Transform>();

		Core::Ray ray
		{
			.origin = playerTransform.position,
			.direction = Core::Camera::MainCamera->GetForwardVec(),
		};

		Core::RayResultRectCollider result = Core::Hits(ray, squareTransform, squareRectCollider);
		if (result.hit)
		{
			//POG_TRACE("{0}, {1}, {2}", result.pointOfIntersection.x, result.pointOfIntersection.y, result.pointOfIntersection.z);
			//POG_WARN("{0}, {1}", result.pointOnRect.x, result.pointOnRect.y);
		}
	}

	void ExampleScene::Frame(float alpha)
	{
		float r = ((float)rand() / (RAND_MAX)) / 3.0f + 0;
		float g = ((float)rand() / (RAND_MAX)) / 3.0f + 0;
		float b = ((float)rand() / (RAND_MAX)) / 3.0f + 0;

		Graphics::ClearColour(r, g, b, 1.0f);
		Graphics::ClearColourBuffer();
		Graphics::ClearDepthBuffer();

		Graphics::SetPolygonMode(POG_FRONT_AND_BACK, POG_FILL);
		//Graphics::SetFrontFace(POG_CW);
		//Graphics::FaceCulling(false);
		//Graphics::CullFace(POG_BACK);
		Graphics::DepthTest(true);
		Graphics::Blend(true);
	}
}