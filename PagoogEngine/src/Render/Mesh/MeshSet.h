#pragma once

#include "Mesh.h"
#include "Render/Core/Objects/IndexBuffer.h"
#include "Render/Core/Objects/VertexArray.h"
#include "Render/Core/Objects/VertexBuffer.h"

namespace PEngine
{
	/// <summary>
	/// A set of meshes with a common vbo, ibo and vao.
	/// </summary>
	class MeshSet
	{
		friend class Mesh;

	public:
		virtual ~MeshSet();

		virtual void Build() = 0;

		virtual void RenderMesh(const Mesh& mesh) = 0;

	protected:
		MeshSet();

		// Adds a mesh to the set. To be used to render, mesh must not go out scope.
		virtual void AddMesh(Mesh& mesh) = 0;

		VertexBuffer& GetVBO() { return vbo; }
		IndexBuffer& GetIBO() { return ibo; }
		VertexArray& GetVAO() { return vao; }

	private:
		VertexBuffer vbo;
		IndexBuffer ibo;
		VertexArray vao;
	};
}


