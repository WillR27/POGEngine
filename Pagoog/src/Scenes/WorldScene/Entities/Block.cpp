#include "pgpch.h"
#include "Block.h"

#include "Render/Mesh/MeshManager.h"

namespace Pagoog
{
	Block::Block(EntityInfo entityInfo, ECSManager& ecsManager)
		: Entity::Entity(entityInfo, ecsManager)
	{
	}

	void Block::OnCreate()
	{
		AddComponent(ECSTransform
			{
				.position = Vec3(0.0f, 0.0f, 0.0f),
				.orientation = Quat(Vec3(0.0f, 0.0f, 0.0f)),
				.scale = Vec3(1.0f, 1.0f, 1.0f),

				.prevPosition = Vec3(0.0f, 0.0f, 0.0f),
				.prevOrientation = Quat(Vec3(0.0f, 0.0f, 0.0f)),
				.prevScale = Vec3(1.0f, 1.0f, 1.0f)
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

		AddComponent(ECSMeshRenderer
			{
				.mesh = nullptr,
				.material = nullptr
			});
	}
}