#pragma once

#include "Game/GameObject/GameObject.h"
#include "Game/GameObject/Components/Transform.h"
#include "Game/GameObject/Components/RigidBody.h"
#include "Game/GameObject/Components/BoxCollider.h"
#include "Game/GameObject/Components/MeshRenderer.h"

namespace Pagoog
{
	class Block : public GameObject
	{
	public:
		Block();
		virtual ~Block() = default;

		virtual void AddInitialComponents() override;
	};
}

