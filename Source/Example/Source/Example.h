#pragma once

#include "POGCore.h"
#include "POGGraphics.h"

namespace Example
{
	class ExampleApplication : public POG::Core::Application
	{
	public:
		ExampleApplication();

		void Init() override;

		void TryUpdate(float timeBetweenLoops) override;
		void TryFrame(float timeBetweenLoops) override;

		void Input(POG::Core::InputPackage& inputPackage, float dt) override;
		void Update(float dt) override;
		void Frame(float alpha) override;
	};
}