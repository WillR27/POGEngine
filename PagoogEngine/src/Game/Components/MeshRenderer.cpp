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

	void MeshRenderer::Render()
	{
		material->GetShader().Use();
		material->UpdateShaderUniforms();

		Transform* transform = dynamic_cast<Transform*>(this);
		if (transform != nullptr)
		{
			material->GetShader().SetMatrix4fv("model", 1, false, transform->ModelMatrix());
		}

		mesh->Render();
	}

	void MeshRenderer::SetMesh(Mesh& mesh)
	{
		this->mesh = &mesh;
	}
	
	void MeshRenderer::SetMaterial(Material& material)
	{
		this->material = &material;
	}
}