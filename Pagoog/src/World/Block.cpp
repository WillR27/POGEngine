#include "pgpch.h"
#include "Block.h"

namespace Pagoog
{
	Block::Block()
	{
		AddComponent<BoxCollider>({ 2.0f, 2.0f, 2.0f });
		AddComponent<MeshRenderer>();
		AddComponent<RigidBody>();
		AddComponent<Transform>();
	}

	void Block::Init()
	{

	}
}