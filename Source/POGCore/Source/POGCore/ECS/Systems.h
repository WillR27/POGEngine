#pragma once

#include "Components.h"
#include "ECSManager.h"

namespace POG::Core
{
	class MeshRendererSystem : public System
	{
	public:
		MeshRendererSystem(ECSManager& ecsManager)
			: System::System(ecsManager)
		{
		}

		static Signature GetSignature(ECSManager& ecsManager);

		void Frame(float alpha);
	};

	class TransformSystem : public System
	{
	public:
		TransformSystem(ECSManager& ecsManager)
			: System::System(ecsManager)
		{
		}

		static Signature GetSignature(ECSManager& ecsManager);

		void Update(float dt);
	};
}