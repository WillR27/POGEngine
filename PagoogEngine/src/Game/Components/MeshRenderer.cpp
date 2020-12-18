#include "pgepch.h"
#include "MeshRenderer.h"

#include "Transform.h"

namespace PEngine
{
	MeshRenderer::MeshRenderer()
		: mesh(nullptr)
		, material(nullptr)
		, position(Vec3(0.0f, 0.0f, 0.0f))
		, orientation(Quaternion(Vec3(0.0f, 0.0f, 0.0f)))
		, scale(Vec3(1.0f, 1.0f, 1.0f))
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
			position = Maths::Lerp(position, transform->GetPosition(), dt);
			orientation = Maths::Lerp(orientation, transform->GetOrientation(), dt);
			scale = Maths::Lerp(scale, transform->GetScale(), dt);

			material->GetShader().SetMatrix4fv("model", 1, false, ToModelMatrix());
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

	Mat4 MeshRenderer::ToModelMatrix() const
	{
		return Maths::ToModelMatrix(position, orientation, scale);
	}
}