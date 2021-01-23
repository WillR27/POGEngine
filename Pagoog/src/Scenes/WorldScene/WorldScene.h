#pragma once

#include "Render/Mesh/Mesh.h"
#include "Render/Mesh/MeshSet.h"
#include "Render/Core/Shader.h"
#include "Render/Material/Material.h"
#include "Render/Mesh/StaticMeshSet.h"
#include "Render/Mesh/Primitives/Primitives.h"
#include "Scene/Scene.h"

#include "Entities/Player.h"

namespace Pagoog
{
	class WorldScene : public Scene
	{
	public:
		WorldScene();
		virtual ~WorldScene();

		virtual void Init() override;

		virtual void Update(float dt) override;
		virtual void FrameUpdate(float alpha) override;

		virtual void HandleEvent(Event& e) override;

		void ActionCallback(InputPackage& inputPackage, float dt);

	private:
		Shared<MeshRendererSystem> meshRendererSystem;

		Player player;



		StaticMeshSet meshSet;
		Mesh mesh1, mesh2, mesh3, mesh4;

		Material material1;
		Shader shader;
	};
}

