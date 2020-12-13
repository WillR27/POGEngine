#include "pgepch.h"
#include "MeshSet.h"

namespace PEngine
{
	MeshSet::MeshSet()
		: vbo()
		, ebo()
		, vao()
	{
	}

	MeshSet::~MeshSet()
	{
	}

	void MeshSet::Build()
	{
	}

	VertexBuffer& MeshSet::GetVBO()
	{
		return vbo;
	}

	IndexBuffer& MeshSet::GetEBO()
	{
		return ebo;
	}

	VertexArray& MeshSet::GetVAO()
	{
		return vao;
	}
}