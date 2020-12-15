#pragma once

#include "Render/Core/Objects/IndexBuffer.h"
#include "Render/Core/Objects/VertexArray.h"
#include "Render/Core/Objects/VertexBuffer.h"

#include "Mesh.h"

namespace PEngine
{
	/// <summary>
	/// A set of meshes with a common vbo, ibo and vao.
	/// </summary>
	class MeshSet
	{
	public:
		virtual ~MeshSet();

		virtual void Build() = 0;

		/// <summary>
		/// Adds a mesh to the set. To be used to render, mesh must not go out scope.
		/// </summary>
		virtual void AddMesh(Mesh& mesh) = 0;

		virtual void RenderMesh(const Mesh& mesh) = 0;

	protected:
		MeshSet();

		VertexBuffer& GetVBO();
		IndexBuffer& GetIBO();
		VertexArray& GetVAO();

	private:
		VertexBuffer vbo;
		IndexBuffer ibo;
		VertexArray vao;
	};
}


