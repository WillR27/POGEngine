#pragma once

#include "Scene/Scene.h"

namespace Pagoog
{
	class WorldScene : public Scene
	{
	public:
		WorldScene();
		virtual ~WorldScene();

		virtual void Init() override;

		virtual void Update(float dt) override;
		virtual void FrameUpdate(float alpha) override;

		virtual void HandleEvent(Event& e) override;

	private:
	};
}

