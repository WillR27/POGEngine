#pragma once

#include "BaseComponent.h"
#include "Render/Mesh/Mesh.h"
#include "Render/Material/Material.h"

namespace PEngine
{
	class MeshRenderer : public BaseComponent
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		void Render();

		void SetMesh(Mesh& mesh);
		void SetMaterial(Material& material);

	private:
		Mesh* mesh;
		Material* material;
	};
}

