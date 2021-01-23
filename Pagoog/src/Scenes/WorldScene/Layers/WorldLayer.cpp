#include "pgpch.h"
#include "WorldLayer.h"

namespace Pagoog
{
	WorldLayer::WorldLayer()
		: Layer::Layer("World")
	{
	}

	WorldLayer::~WorldLayer()
	{
	}

	void WorldLayer::Init()
	{
		Layer::Init();
	}

	void WorldLayer::Update(float dt)
	{
		Layer::Update(dt);
	}

	void WorldLayer::FrameUpdate(float alpha)
	{
		Layer::FrameUpdate(alpha);
	}

	void WorldLayer::HandleEvent(Event& e)
	{
		Layer::HandleEvent(e);
	}
}