#pragma once

#include "ECS/ECS.h"
#include "Event/Event.h"
#include "Input/InputManager.h"

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

	class Layer
	{
	public:
		Layer(const char* name);
		virtual ~Layer();

		virtual void PreInit();
		virtual void Init();
		virtual void PostInit();

		virtual void PreInputUpdate(float dt);
		virtual void InputUpdate(float dt);
		virtual void PostInputUpdate(float dt);

		virtual void PreUpdate(float dt);
		virtual void Update(float dt);
		virtual void PostUpdate(float dt);

		virtual void CollisionsPreUpdate(float dt);
		virtual void CollisionsUpdate(float dt);
		virtual void CollisionsPostUpdate(float dt);

		virtual void PreFrameUpdate(float alpha);
		virtual void FrameUpdate(float alpha);
		virtual void PostFrameUpdate(float alpha);

		virtual void PreHandleEvent(Event& e);
		virtual void HandleEvent(Event& e);
		virtual void PostHandleEvent(Event& e);

		const char* GetName() const { return name; }

	protected:
		const char* name;

		InputManager inputManager;

		ECSManager ecsManager;

		Shared<RayCastSystem> rayCastSystem;

	private:
		Shared<TransformSystem> transformSystem;
		Shared<PhysicsSystem> physicsSystem;
		Shared<CollisionsSystem> collisionsSystem;
		Shared<MeshRendererSystem> meshRendererSystem;
		Shared<CameraUpdateViewSystem> cameraUpdateViewSystem;
	};
}

