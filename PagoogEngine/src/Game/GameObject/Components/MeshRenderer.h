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

		void Render(float dt);

		const Mesh& GetMesh() const;
		void SetMesh(Mesh& mesh);

		Material& GetMaterial() const;
		void SetMaterial(Material& material);

		Mat4 ToModelMatrix() const;

	private:
		Mesh* mesh;
		Material* material;

		Vec3 position;
		Quat orientation;
		Vec3 scale;
	};
}

