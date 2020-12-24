#pragma once

#include "Game/GameObject/Components/Transform.h"
#include "Game/GameObject/Components/RigidBody.h"
#include "Game/GameObject/Components/BoxCollider.h"
#include "Game/GameObject/Components/MeshRenderer.h"

namespace Pagoog
{
	class Block 
		: public PEngine::Transform
		, public PEngine::RigidBody
		, public PEngine::BoxCollider
		, public PEngine::MeshRenderer
	{
	public:
		Block();
		virtual ~Block() = default;
	};
}

