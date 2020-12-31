#include "pgpch.h"
#include "Block.h"

namespace Pagoog
{
	Block::Block()
	{
	}

	void Block::AddInitialComponents()
	{
		AddComponent<Transform>();
		AddComponent<RigidBody>();
		AddComponent<BoxCollider>();
		AddComponent<MeshRenderer>();
	}
}