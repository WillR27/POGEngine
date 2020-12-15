#pragma once

#include "Game/Components/MeshRenderer.h"
#include "Game/Components/Transform.h"

namespace Pagoog
{
	class Block : public PEngine::Transform, public PEngine::MeshRenderer
	{
	public:
		Block();
		virtual ~Block() = default;
	};
}

