#pragma once

#include "Render/Mesh/Mesh.h"
#include "Render/Material/Material.h"

namespace PEngine
{
	class MeshRenderer
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		void Render();

		void SetMesh(Mesh& mesh);
		void SetMaterial(Material& material);

	private:
		Mesh* mesh;
		Material* material;
	};
}

