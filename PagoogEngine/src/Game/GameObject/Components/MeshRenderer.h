#pragma once

#include "Render/Mesh/Mesh.h"
#include "Render/Material/Material.h"
#include "Game/GameObject/GameObject.h"

namespace PEngine
{
	class MeshRenderer : public virtual GameObject
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		void Render(float dt);

		const Mesh& GetMesh() const;
		void SetMesh(Mesh& mesh);

		Material& GetMaterial() const;
		void SetMaterial(Material& material);

	private:
		Mesh* mesh;
		Material* material;
	};
}

