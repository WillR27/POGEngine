#pragma once

#include "ECS/Systems.h"
#include "Event/Event.h"
#include "Layer/Layer.h"
#include "Render/Material/MaterialManager.h"
#include "Render/Mesh/MeshManager.h"
#include "Render/Shader/ShaderManager.h"

namespace PEngine
{
	class Scene
	{
	public:
		friend class Application;
		friend class ECSManager;

		Scene(std::string name = "Scene");
		virtual ~Scene();

		void PreInit();
		virtual void Init() = 0;
		void PostInit();

		void PreUpdate(float dt);
		virtual void Update(float dt) = 0;
		void PostUpdate(float dt);

		void PreFrameUpdate(float alpha);
		virtual void FrameUpdate(float alpha) = 0;
		void PostFrameUpdate(float alpha);

		void PreHandleEvent(Event& e);
		virtual void HandleEvent(Event& e) = 0;
		void PostHandleEvent(Event& e);

		std::string GetName() const { return name; }

		InputManager& GetInputManager() { return inputManager; }
		ECSManager& GetECSManager() { return ecsManager; }
		MeshManager& GetMeshManager() { return meshManager; }
		MaterialManager& GetMaterialManager() { return materialManager; }
		ShaderManager& GetShaderManager() { return shaderManager; }

	private:
		InputManager inputManager;
		ECSManager ecsManager;
		MeshManager meshManager;
		MaterialManager materialManager;
		ShaderManager shaderManager;

		static Scene* ActiveScene;

		std::string name;
	};
}

