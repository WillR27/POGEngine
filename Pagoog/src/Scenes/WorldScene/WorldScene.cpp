#include "pgpch.h"
#include "WorldScene.h"

#include "Layers/WorldLayer.h"

namespace Pagoog
{
	WorldScene::WorldScene()
		: Scene::Scene("World")
	{
	}

	WorldScene::~WorldScene()
	{
	}

	void WorldScene::Init()
	{
		AddLayer(new WorldLayer());

		Scene::Init();
	}

	void WorldScene::Update(float dt)
	{
		Scene::Update(dt);
	}

	void WorldScene::FrameUpdate(float alpha)
	{
		Scene::FrameUpdate(alpha);
	}

	void WorldScene::HandleEvent(Event& e)
	{
		Scene::HandleEvent(e);
	}
}