#include "pgepch.h"
#include "MeshRenderer.h"

#include "Transform.h"

namespace PEngine
{
	MeshRenderer::MeshRenderer()
		: mesh(nullptr)
		, material(nullptr)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
		if (&mesh == nullptr)
		{
			PG_WARN("Deleted a mesh renderer before a mesh was set. Are you sure you wanted to do this?");
		}

		if (&material == nullptr)
		{
			PG_WARN("Deleted a mesh renderer before a material was set. Are you sure you wanted to do this?");
		}
	}

	void MeshRenderer::Render(float dt)
	{
		material->GetShader().Use();
		material->UpdateShaderUniforms();

		Transform* transform = dynamic_cast<Transform*>(this);
		if (transform != nullptr)
		{
			Vec3 position = glm::mix(transform->GetPrevPosition(), transform->GetPosition(), dt);
			Quaternion orientation = glm::mix(transform->GetPrevOrientation(), transform->GetOrientation(), dt);
			transform->SetPrevPosition(position);
			transform->SetPrevOrientation(orientation);

			Mat4 model(1.0f);
			model = Maths::Translate(model, position);
			model = Maths::Rotate(model, Maths::ToMatrix(orientation));
			material->GetShader().SetMatrix4fv("model", 1, false, model);
		}

		mesh->Render();
	}

	const Mesh& MeshRenderer::GetMesh() const
	{
		return *mesh;
	}

	void MeshRenderer::SetMesh(Mesh& mesh)
	{
		this->mesh = &mesh;
	}
	
	Material& MeshRenderer::GetMaterial() const
	{
		return *material;
	}

	void MeshRenderer::SetMaterial(Material& material)
	{
		this->material = &material;
	}
}