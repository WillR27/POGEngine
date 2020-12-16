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

using namespace PEngine;

namespace Pagoog
{
	class WorldLayer : public Layer
	{
	public:
		WorldLayer();
		virtual ~WorldLayer();

		virtual void Init() override;
		virtual void Update() override;
		virtual void HandleEvent(Event& e) override;

		void ActionCallback(std::vector<Action>& actions);

	private:
		StaticMeshSet meshSet;

		Mesh mesh, mesh2, mesh3, mesh4;

		Material material1;

		Shader shader;

		Block block;
	};
}

