#pragma once

#include "Event/Event.h"
#include "Input/InputManager.h"

#include "Game/GameObject/Components/Components.h"

#include "ECS/ECS.h"

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

	class GameObject;

	class Layer
	{
	public:
		friend class Scene;

		Layer(const char* name);
		virtual ~Layer();

		virtual void Init() = 0;
	
		virtual void CollisionsUpdate(float dt) = 0;
		virtual void Update(float dt) = 0;
		virtual void FrameUpdate(float dt) = 0;

		void PreHandleEvent(Event& e);
		virtual void HandleEvent(Event& e) = 0;

		const char* GetName() const;

	protected:
		const char* name;

		InputManager inputManager;

		ECSManager ecsManager;

		Shared<RayCastSystem> rayCastSystem;

	private:
		static Layer* ActiveLayer;

		std::vector<GameObject*> gameObjects;
		std::vector<BoxCollider*> boxColliders;
		std::vector<Camera*> cameras;
		std::vector<MeshRenderer*> meshRenderers;
		std::vector<RigidBody*> rigidBodies;
		std::vector<Transform*> transforms;

		void PreInit();

		void InputUpdate(float dt);

		void PreUpdate(float dt);
		void PostUpdate(float dt);

		void CollisionsPreUpdate(float dt);
		void CollisionsPostUpdate(float dt);

		void PreFrameUpdate(float dt);
		void PostFrameUpdate(float dt);

		Shared<TransformSystem> transformSystem;
		Shared<PhysicsSystem> physicsSystem;
		Shared<CollisionsSystem> collisionsSystem;
		Shared<MeshRendererSystem> meshRendererSystem;
		Shared<CameraUpdateViewSystem> cameraUpdateViewSystem;
	};
}

