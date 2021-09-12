#pragma once

#include "POGCore/ECS/ECS.h"
#include "POGCore/Event/Event.h"
#include "POGCore/Input/InputPackage.h"

namespace POG::Core
{
	class Scene
	{
	public:
		static Scene& GetActiveScene();
		static void SetActiveScene(std::shared_ptr<Scene> scene);

		Scene() = default;

		virtual ~Scene() = default;

		void PreInit();
		virtual void Init();
		void PostInit();

		virtual void Exit();

		virtual void Input(InputPackage& inputPackage, float dt);

		void PreUpdate(float dt);
		virtual void Update(float dt);
		void PostUpdate(float dt);

		void PreFrame(float alpha);
		virtual void Frame(float alpha);
		void PostFrame(float alpha);

		ECSManager& GetECSManager() { return ecsManager; }

		CameraUpdateViewSystem& GetCameraUpdateViewSystem() { return *cameraUpdateViewSystem; }
		MeshRendererSystem& GetMeshRendererSystem() { return *meshRendererSystem; }
		PhysicsSystem& GetPhysicsSystem() { return *physicsSystem; }
		SpriteBoxCollider2DRendererSystem& GetSpriteBoxCollider2DRendererSystem() { return *spriteBoxCollider2DRendererSystem; }
		SpriteRectColliderRendererSystem& GetSpriteRectColliderRendererSystem() { return *spriteRectColliderRendererSystem; }
		SpriteRendererSystem& GetSpriteRendererSystem() { return *spriteRendererSystem; }
		TransformSystem& GetTransformSystem() { return *transformSystem; }

	private:
		static std::shared_ptr<Scene> ActiveScene;
		
		ECSManager ecsManager;

		std::shared_ptr<CameraUpdateViewSystem> cameraUpdateViewSystem;
		std::shared_ptr<MeshRendererSystem> meshRendererSystem;
		std::shared_ptr<PhysicsSystem> physicsSystem;
		std::shared_ptr<SpriteBoxCollider2DRendererSystem> spriteBoxCollider2DRendererSystem;
		std::shared_ptr<SpriteRectColliderRendererSystem> spriteRectColliderRendererSystem;
		std::shared_ptr<SpriteRendererSystem> spriteRendererSystem;
		std::shared_ptr<TransformSystem> transformSystem;
	};
}

