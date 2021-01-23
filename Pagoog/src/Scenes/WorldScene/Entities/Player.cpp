#include "pgpch.h"
#include "Player.h"

#include "Scene/Camera.h"

namespace PEngine
{
    Entity Player::Create(ECSManager& ecsManager)
    {
		Entity entity = ecsManager.CreateEntity();

		entity.AddComponent(ECSTransform
			{
				.position = Vec3(0.0f, 0.0f, 10.0f),
				.orientation = Quat(Vec3(0.0f, 0.0f, 0.0f)),
				.scale = Vec3(1.0f, 1.0f, 1.0f)
			});

		entity.AddComponent(ECSRigidBody
			{
				.force = Vec3(0.0f, 0.0f, 0.0f),
				.velocity = Vec3(0.0f, 0.0f, 0.0f),
				.mass = 1.0f,
				.dragCoef = 1.0f
			});

		entity.AddComponent(ECSBoxCollider
			{
				.aabb = AABB<3>({ 2.0f, 2.0f, 2.0f }),
				.stickiness = 0.5f
			});

		entity.AddComponent(ECSCamera
			{
				.camera = Camera::MainCamera
			});

		return entity;
    }
}