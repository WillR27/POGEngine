#pragma once

#include "ECS.h"

namespace PEngine
{
	class TransformSystem : public System
	{
	public:
		TransformSystem(ECSManager& ecsManager)
			: ecsManager(ecsManager)
		{
		}

		void Update(float dt);

		static Signature GetSignature(ECSManager& ecsManager)
		{
			Signature signature;
			signature.set(ecsManager.GetComponentTypeId<ECSTransform>());
			return signature;
		}

	private:
		ECSManager& ecsManager;
	};

	class PhysicsSystem : public System
	{
	public:
		PhysicsSystem(ECSManager& ecsManager)
			: ecsManager(ecsManager)
		{
		}

		void Update(float dt);

		static Signature GetSignature(ECSManager& ecsManager)
		{
			Signature signature;
			signature.set(ecsManager.GetComponentTypeId<ECSTransform>());
			signature.set(ecsManager.GetComponentTypeId<ECSRigidBody>());
			return signature;
		}

	private:
		ECSManager& ecsManager;
	};

	class CollisionsSystem : public System
	{
	public:
		CollisionsSystem(ECSManager& ecsManager)
			: ecsManager(ecsManager)
		{
		}

		void Update(float dt);

		static Signature GetSignature(ECSManager& ecsManager)
		{
			Signature signature;
			signature.set(ecsManager.GetComponentTypeId<ECSTransform>());
			signature.set(ecsManager.GetComponentTypeId<ECSRigidBody>());
			signature.set(ecsManager.GetComponentTypeId<ECSBoxCollider>());
			return signature;
		}

	private:
		ECSManager& ecsManager;
	};

	class CameraUpdateViewSystem : public System
	{
	public:
		CameraUpdateViewSystem(ECSManager& ecsManager)
			: ecsManager(ecsManager)
		{
		}

		void UpdateView();

		static Signature GetSignature(ECSManager& ecsManager)
		{
			Signature signature;
			signature.set(ecsManager.GetComponentTypeId<ECSTransform>());
			signature.set(ecsManager.GetComponentTypeId<ECSCamera>());
			return signature;
		}

	private:
		ECSManager& ecsManager;
	};

	class MeshRendererSystem : public System
	{
	public:
		MeshRendererSystem(ECSManager& ecsManager)
			: ecsManager(ecsManager)
		{
		}

		void FrameUpdate(float alpha);

		static Signature GetSignature(ECSManager& ecsManager)
		{
			Signature signature;
			signature.set(ecsManager.GetComponentTypeId<ECSTransform>());
			signature.set(ecsManager.GetComponentTypeId<ECSMeshRenderer>());
			return signature;
		}

	private:
		ECSManager& ecsManager;
	};

	struct RayCastResult
	{
		bool hit = false;
		EntityId entityId = 0;
	};

	class RayCastSystem : public System
	{
	public:
		RayCastSystem(ECSManager& ecsManager)
			: ecsManager(ecsManager)
		{
		}

		RayCastResult RayCast(Vec3 position, Vec3 direction, EntityId entityIdToIgnore);

		static Signature GetSignature(ECSManager& ecsManager)
		{
			Signature signature;
			signature.set(ecsManager.GetComponentTypeId<ECSTransform>());
			signature.set(ecsManager.GetComponentTypeId<ECSBoxCollider>());
			return signature;
		}

	private:
		ECSManager& ecsManager;
	};
}