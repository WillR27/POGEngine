#pragma once

#include "Event/Event.h"
#include "Input/InputManager.h"

#include "Game/GameObject/Components/Components.h"

#include "ECS/ECSCoordinator.h"
#include "ECS/Component/Components.h"

namespace PEngine
{
	class TransformSystem : public System
	{
	public:
		static Signature GetSignature(ECSCoordinator& coordinator)
		{
			Signature signature;
			signature.set(coordinator.GetComponentType<ECSTransform>());

			return signature;
		}

		void Update(float dt, ECSCoordinator& coordinator);
	};

	class PhysicsSystem : public System
	{
	public:
		static Signature GetSignature(ECSCoordinator& coordinator)
		{
			Signature signature;
			signature.set(coordinator.GetComponentType<ECSTransform>());
			signature.set(coordinator.GetComponentType<ECSRigidBody>());

			return signature;
		}

		void Update(float dt, ECSCoordinator& coordinator);
	};

	class CollisionsSystem : public System
	{
	public:
		static Signature GetSignature(ECSCoordinator& coordinator)
		{
			Signature signature;
			signature.set(coordinator.GetComponentType<ECSTransform>());
			signature.set(coordinator.GetComponentType<ECSRigidBody>());
			signature.set(coordinator.GetComponentType<ECSBoxCollider>());

			return signature;
		}

		void Update(float dt, ECSCoordinator& coordinator);
	};

	class CameraUpdateViewSystem : public System
	{
	public:
		static Signature GetSignature(ECSCoordinator& coordinator)
		{
			Signature signature;
			signature.set(coordinator.GetComponentType<ECSTransform>());
			signature.set(coordinator.GetComponentType<ECSCamera>());

			return signature;
		}

		void UpdateView(ECSCoordinator& coordinator);
	};

	class MeshRendererSystem : public System
	{
	public:
		static Signature GetSignature(ECSCoordinator& coordinator)
		{
			Signature signature;
			signature.set(coordinator.GetComponentType<ECSTransform>());
			signature.set(coordinator.GetComponentType<ECSMeshRenderer>());

			return signature;
		}

		void FrameUpdate(float alpha, ECSCoordinator& coordinator);
	};

	class RayCastSystem : public System
	{
	public:
		static Signature GetSignature(ECSCoordinator& coordinator)
		{
			Signature signature;
			signature.set(coordinator.GetComponentType<ECSTransform>());
			signature.set(coordinator.GetComponentType<ECSBoxCollider>());

			return signature;
		}

		Entity RayCast(ECSCoordinator& coordinator, Vec3 position, Vec3 direction, Entity entityToIgnore);
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

		ECSCoordinator coordinator;

		Shared<RayCastSystem> rayCastSystem;

	private:
		static Layer* ActiveLayer;

		std::vector<GameObject*> gameObjects;
		std::vector<BoxCollider*> boxColliders;
		std::vector<Camera*> cameras;
		std::vector<MeshRenderer*> meshRenderers;
		std::vector<RigidBody*> rigidBodies;
		std::vector<Transform*> transforms;

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

