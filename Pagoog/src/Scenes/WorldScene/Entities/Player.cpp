#include "pgpch.h"
#include "Player.h"

#include "Input/Input.h"
#include "Scene/Camera.h"

namespace Pagoog
{
	Player::Player(EntityInfo entityInfo, ECSManager& ecsManager, float moveSpeed, float sprintMultiplier, float lookSpeed)
		: Entity::Entity(entityInfo, ecsManager)
		, moveSpeed(moveSpeed)
		, sprintMultiplier(sprintMultiplier)
		, lookSpeed(lookSpeed)
	{
	}

	void Player::OnCreate()
	{
		AddComponent(ECSTransform
			{
				.position = Vec3(0.0f, 0.0f, 10.0f),
				.orientation = Quat(Vec3(0.0f, 0.0f, 0.0f)),
				.scale = Vec3(1.0f, 1.0f, 1.0f)
			});

		AddComponent(ECSRigidBody
			{
				.force = Vec3(0.0f, 0.0f, 0.0f),
				.velocity = Vec3(0.0f, 0.0f, 0.0f),
				.mass = 1.0f,
				.dragCoef = 1.0f
			});

		AddComponent(ECSBoxCollider
			{
				.aabb = AABB<3>({ 2.0f, 2.0f, 2.0f }),
				.stickiness = 0.5f
			});

		AddComponent(ECSCamera
			{
				.camera = Camera::MainCamera
			});
	}

	void Player::InputCallback(PEngine::InputPackage& inputPackage, float dt)
	{
		auto& playerTransform = GetComponent<ECSTransform>();
		auto& playerRigidBody = GetComponent<ECSRigidBody>();
		auto& playerCamera = GetComponent<ECSCamera>();

		if (inputPackage.HasMouseMoved())
		{
			playerCamera.camera->AddPitchAndYaw(Input::GetDeltaMouseY() * dt * lookSpeed, Input::GetDeltaMouseX() * dt * lookSpeed);
		}

		float moveSpeed = inputPackage.IsStateActive("Sprint") ? this->moveSpeed * sprintMultiplier : this->moveSpeed;
		playerRigidBody.velocity =
			(((playerCamera.camera->GetForwardVec() * static_cast<float>(inputPackage.GetAxisValue("Vertical"))) +
				(playerCamera.camera->GetRightVec() * static_cast<float>(inputPackage.GetAxisValue("Horizontal")))) +
				Vec3(0.0f, static_cast<float>(inputPackage.GetAxisValue("Fly")), 0.0f)) * moveSpeed;

		if (inputPackage.HasActionOccurred("Left"))
		{
			RayCastResult rayCastResult = GetECSManager().rayCastSystem->RayCast(playerTransform.position, playerCamera.camera->GetForwardVec(), GetId());

			if (rayCastResult.hit)
			{
				GetECSManager().DestroyEntity(rayCastResult.entityId);
			}
		}
	}
}