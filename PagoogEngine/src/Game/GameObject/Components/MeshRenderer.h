#pragma once

#include "Render/Mesh/Mesh.h"
#include "Render/Material/Material.h"
#include "Game/GameObject/Components/Component.h"

namespace PEngine
{
	class MeshRenderer : public _Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual _Component* Clone() const override;

		void FrameUpdate(float dt);

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

