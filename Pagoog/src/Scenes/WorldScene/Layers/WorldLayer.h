#pragma once

#include "ECS/ECS.h"
#include "Layer/Layer.h"
#include "Render/Core/Render.h"
#include "Render/Core/Objects/VertexBuffer.h"
#include "Render/Core/Objects/IndexBuffer.h"
#include "Render/Core/Objects/VertexArray.h"
#include "Render/Core/Shader.h"
#include "Render/Mesh/StaticMeshSet.h"
#include "Render/Material/Material.h"

namespace Pagoog
{
	class WorldLayer : public Layer
	{
	public:
		WorldLayer();
		virtual ~WorldLayer();

		virtual void Init() override;

		virtual void Update(float dt) override;
		virtual void FrameUpdate(float alpha) override;

		virtual void HandleEvent(Event& e) override;

		void ActionCallback(InputPackage& inputPackage, float dt);

	private:
		StaticMeshSet meshSet;
		Mesh mesh1, mesh2, mesh3, mesh4;

		Material material1;
		Shader shader;

		Entity player;
	};
}