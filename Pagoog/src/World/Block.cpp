#include "pgpch.h"
#include "Block.h"

namespace Pagoog
{
	Block::Block()
	{
		AddComponent<BoxCollider>();
		AddComponent<MeshRenderer>();
		AddComponent<RigidBody>();
		AddComponent<Transform>();
	}

	void Block::Init()
	{

	}
}