#pragma once

#include "Layer/Layer.h"

#include "Render/Core/Render.h"
#include "Render/Core/Objects/VertexBuffer.h"
#include "Render/Core/Objects/IndexBuffer.h"
#include "Render/Core/Objects/VertexArray.h"
#include "Render/Core/Shader.h"
#include "Render/Mesh/StaticMeshSet.h"
#include "Render/Material/Material.h"

#include "World/Player.h"

#include "ECS/Component/Components.h"

namespace Pagoog
{
	class ECSLayer : public Layer
	{
	public:
		ECSLayer();
		virtual ~ECSLayer();

		virtual void Init() override;

		virtual void CollisionsUpdate(float dt) override;
		virtual void Update(float dt) override;
		virtual void FrameUpdate(float alpha) override;

		virtual void HandleEvent(Event& e) override;

		void ActionCallback(InputPackage& inputPackage, float dt);

	private:
		StaticMeshSet meshSet;
		Mesh mesh, mesh2, mesh3, mesh4;

		Material material1;
		Shader shader;

		Entity player;
		Player* player2;
	};
}