#pragma once

#include "Render/Mesh/Mesh.h"
#include "Render/Mesh/MeshSet.h"
#include "Render/Material/Material.h"
#include "Render/Mesh/Primitives/Primitives.h"
#include "Render/Shader/Shader.h"
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

		void InputCallback(InputPackage& inputPackage, float dt);

	private:
		Shared<MeshRendererSystem> meshRendererSystem;

		Player player;
	};
}

