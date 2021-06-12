#pragma once

#include "POGCore.h"
#include "POGGraphics.h"

#include "Player.h"

namespace Example
{
	class ExampleScene : public POG::Core::Scene
	{
	public:
		ExampleScene() = default;

		virtual ~ExampleScene() = default;

		void Init() override;

		void Exit() override;

		void Input(POG::Core::InputPackage& inputPackage, float dt) override;
		void Update(float dt) override;
		void Frame(float alpha) override;

	private:
		Player player;
		POG::Core::Entity square;
		POG::Core::Entity child;

		bool flip;
	};
}

