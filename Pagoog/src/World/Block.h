#pragma once

#include "Game/GameObject/GameObject.h"
#include "Game/GameObject/Components/Components.h"

namespace Pagoog
{
	class Block : public GameObject
	{
	public:
		Block();
		virtual ~Block() = default;

		virtual void Init() override;
	};
}

