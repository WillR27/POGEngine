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
}