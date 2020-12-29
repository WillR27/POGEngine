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

	void MeshRenderer::Render(float alpha)
	{
		material->GetShader().Use();
		material->UpdateShaderUniforms();

		Transform* transform = dynamic_cast<Transform*>(this);
		if (transform != nullptr)
		{
			Vec3 position = Maths::Lerp(transform->GetPrevPosition(), transform->GetPosition(), alpha);
			Quat orientation = Maths::Lerp(transform->GetPrevOrientation(), transform->GetOrientation(), alpha);
			Vec3 scale = Maths::Lerp(transform->GetPrevScale(), transform->GetScale(), alpha);

			material->GetShader().SetMatrix4fv("model", 1, false, Maths::ToModelMatrix(position, orientation, scale));
		}
		else
		{
			material->GetShader().SetMatrix4fv("model", 1, false, Mat4(1.0f));
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