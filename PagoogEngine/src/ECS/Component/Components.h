#pragma once

#include "Maths/Maths.h"

#include "Render/Mesh/Mesh.h"
#include "Render/Material/Material.h"

namespace PEngine
{
	struct ECSTransform
	{
		Vec3 position = Vec3(0.0f, 0.0f, 0.0f);
		Quat orientation = Quat(Vec3(0.0f, 0.0f, 0.0f));
		Vec3 scale = Vec3(1.0f, 1.0f, 1.0f);

		Vec3 prevPosition = Vec3(0.0f, 0.0f, 0.0f);
		Quat prevOrientation = Quat(Vec3(0.0f, 0.0f, 0.0f));
		Vec3 prevScale = Vec3(1.0f, 1.0f, 1.0f);
	};

	struct ECSRigidBody
	{
		Vec3 force = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 velocity = Vec3(0.0f, 0.0f, 0.0f);
		float mass = 1.0f;
		float dragCoef = 1.0f;
	};

	struct ECSBoxCollider
	{
		AABB<3> aabb = AABB<3>({ 1.0f, 1.0f, 1.0f });
		float stickiness = 0.5f;
	};

	struct ECSMeshRenderer
	{
		Mesh* mesh = nullptr;
		Material* material = nullptr;
	};

	struct ECSCamera
	{

	};
}