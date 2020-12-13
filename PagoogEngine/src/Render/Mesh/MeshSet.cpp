#include "pgepch.h"
#include "MeshSet.h"

namespace PEngine
{
	MeshSet::MeshSet()
		: vbo() // TODO: Construct inside build as we may not want an ibo
		, ibo()
		, vao()
	{
	}

	MeshSet::~MeshSet()
	{
	}

	VertexBuffer& MeshSet::GetVBO()
	{
		return vbo;
	}

	IndexBuffer& MeshSet::GetIBO()
	{
		return ibo;
	}

	VertexArray& MeshSet::GetVAO()
	{
		return vao;
	}
}