#include "pgpch.h"
#include "Player.h"

#include "Scene/Camera.h"

namespace PEngine
{
	Player::Player(EntityInfo entityInfo, ECSManager& ecsManager)
		: Entity::Entity(entityInfo, ecsManager)
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
}