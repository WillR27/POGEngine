#pragma once

#include "POGCore/ECS/ECS.h"
#include "POGCore/Event/Event.h"
#include "POGCore/Input/InputPackage.h"

namespace POG::Core
{
	class Scene
	{
	public:
		Scene() = default;

		virtual ~Scene() = default;

		void PreInit();
		virtual void Init() = 0;

		virtual void Exit() = 0;

		virtual void Input(InputPackage& inputPackage, float dt) = 0;
		virtual void Update(float dt) = 0;
		virtual void Frame(float alpha) = 0;

		virtual void HandleEvent(Event& e) = 0;

		ECSManager& GetECSManager() { return ecsManager; }

		MeshRendererSystem& GetMeshRendererSystem() { return *meshRendererSystem; }
		TransformSystem& GetTransformSystem() { return *transformSystem; }

	private:
		ECSManager ecsManager;

		std::shared_ptr<MeshRendererSystem> meshRendererSystem;
		std::shared_ptr<TransformSystem> transformSystem;
	};
}

