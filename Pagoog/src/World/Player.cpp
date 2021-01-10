#include "pgpch.h"
#include "Player.h"

namespace Pagoog
{
	Player::Player()
	{
		AddComponent<BoxCollider>({ 1.0f, 2.0f, 1.0f });
		AddComponent<Camera>();
		AddComponent<RigidBody>();
		AddComponent<Transform>();
	}

	void Player::Init()
	{
	}
}