#pragma once

#include "Game/GameObject/GameObject.h"
#include "Game/GameObject/Components/Components.h"

namespace Pagoog
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player() = default;

		virtual void Init() override;
	};
}

