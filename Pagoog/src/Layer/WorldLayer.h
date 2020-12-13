#pragma once

#include "Layer/Layer.h"

#include "Render/Render.h"
#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"
#include "Render/VertexArray.h"
#include "Render/Shader.h"
#include "Render/Mesh/StaticMeshSet.h"

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

	private:
		Mesh mesh, mesh2, mesh3, mesh4;
		StaticMeshSet meshSet;
		//StaticMeshSet meshSet2;

		Shader shader;

		Block block;

		float a = 0.0f;
	};
}

