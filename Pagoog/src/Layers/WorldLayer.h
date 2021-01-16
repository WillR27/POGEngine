#pragma once

#include "Layer/Layer.h"

#include "Render/Core/Render.h"
#include "Render/Core/Objects/VertexBuffer.h"
#include "Render/Core/Objects/IndexBuffer.h"
#include "Render/Core/Objects/VertexArray.h"
#include "Render/Core/Shader.h"
#include "Render/Mesh/StaticMeshSet.h"
#include "Render/Material/Material.h"

#include "World/Block.h"
#include "World/Player.h"

using namespace PEngine;

namespace Pagoog
{
	class WorldLayer : public Layer
	{
	public:
		WorldLayer();
		virtual ~WorldLayer();

		virtual void Init() override;

		virtual void CollisionsUpdate(float dt) override;
		virtual void Update(float dt) override;
		virtual void FrameUpdate(float dt) override;

		virtual void HandleEvent(Event& e) override;

		void ActionCallback(InputPackage& inputPackage, float dt);

	private:
		StaticMeshSet meshSet;

		Mesh mesh, mesh2, mesh3, mesh4;

		Material material1;

		Shader shader;

		Block templateBlock;
		Safe<Block> block;

		Player* player;
	};
}

