#include "pgpch.h"
#include "Player.h"

namespace Pagoog
{
	Player::Player()
	{
		AddComponent<BoxCollider>({ 1.0f, 2.0f, 1.0f });
		AddComponent<Camera>();
		AddComponent<RigidBody>();
		AddComponent<Transform>();
		AddComponent<MeshRenderer>();
	}

	void Player::Update(float dt)
	{
		
	}

	void Player::ActionCallback(InputPackage& inputPackage, float dt)
	{
		RigidBody* rigidBody = GetComponent<RigidBody>();
		Camera* camera = GetComponent<Camera>();

		float moveSpeed = 1.0f;
		float lookSpeed = 0.1f;

		rigidBody->SetVelocity(
			(((camera->GetForwardVec() * static_cast<float>(inputPackage.GetAxisValue("Vertical"))) + 
			(camera->GetRightVec() * static_cast<float>(inputPackage.GetAxisValue("Horizontal")))) * moveSpeed) +
			Vec3(0.0f, inputPackage.GetAxisValue("Fly"), 0.0f)
		);

		if (inputPackage.HasMouseMoved())
		{
			GetComponent<Camera>()->AddPitchAndYaw(Input::GetDeltaMouseY() * dt * lookSpeed, Input::GetDeltaMouseX() * dt * lookSpeed);
		}
	}
}