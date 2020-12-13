#include "pgepch.h"
#include "MeshRenderer.h"

namespace PEngine
{
	MeshRenderer::MeshRenderer()
	{
	}

	MeshRenderer::~MeshRenderer()
	{
		//PG_ASSERT(mesh, "Deleted a mesh renderer before a mesh was set. Are you sure you wanted to do this?");

		//delete mesh;
	}
}