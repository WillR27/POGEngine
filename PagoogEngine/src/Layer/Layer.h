#pragma once

#include "Event/Event.h"
#include "Input/InputManager.h"
#include "Game/GameObject/GameObject.h"
#include "Game/GameObject/Components/BoxCollider.h"
#include "Game/GameObject/Components/MeshRenderer.h"
#include "Game/GameObject/Components/RigidBody.h"

namespace PEngine
{
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

		virtual void HandleEvent(Event& e);

		const char* GetName() const;

	protected:
		const char* name;

		InputManager inputManager;

	private:
		std::vector<GameObject*> gameObjects;
		std::vector<BoxCollider*> boxColliders;
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
	};
}

