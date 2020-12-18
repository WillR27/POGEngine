#pragma once

#include "Game/Components/Transform.h"
#include "Game/Components/RigidBody.h"
#include "Game/Components/MeshRenderer.h"

namespace Pagoog
{
	class Block 
		: public PEngine::Transform
		, public PEngine::RigidBody
		, public PEngine::MeshRenderer
	{
	public:
		Block();
		virtual ~Block() = default;
	};
}

