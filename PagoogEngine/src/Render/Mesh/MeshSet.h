#pragma once

#include "Render/IndexBuffer.h"
#include "Render/VertexArray.h"
#include "Render/VertexBuffer.h"

#include "Mesh.h"

namespace PEngine
{
	class MeshSet
	{
	public:
		virtual ~MeshSet();

		virtual void Build() = 0;

		virtual void AddMesh(const Mesh& mesh) = 0;

		virtual void RenderMesh(const Mesh& mesh) = 0;

		VertexBuffer& GetVBO();
		IndexBuffer& GetEBO();
		VertexArray& GetVAO();

	protected:
		MeshSet();

	private:
		VertexBuffer vbo;
		IndexBuffer ebo;
		VertexArray vao;
	};
}


