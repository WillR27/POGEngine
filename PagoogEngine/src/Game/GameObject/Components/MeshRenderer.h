#pragma once

#include "Render/Mesh/Mesh.h"
#include "Render/Material/Material.h"
#include "Game/GameObject/Components/Component.h"

namespace PEngine
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		void Render(float dt);

		const Mesh& GetMesh() const;
		void SetMesh(Mesh& mesh);

		Material& GetMaterial() const;
		void SetMaterial(Material& material);

		static constexpr const char* ComponentName()
		{
			return STRINGIFY(MeshRenderer);
		}

		virtual std::string GetComponentName() const override;

	private:
		Mesh* mesh;
		Material* material;
	};
}

