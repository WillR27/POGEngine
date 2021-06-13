#pragma once

#include "POGCore.h"
#include "POGMaths.h"

namespace Example
{
	struct BulletInfo
	{
		float timeExisted = 0.0f;
	};

	class Bullet : public POG::Core::Entity
	{
	public:
		Bullet() = default;
		Bullet(POG::Core::EntityInfo entityInfo, POG::Core::ECSManager& ecsManager, POG::Maths::Vec3 origin, float direction);

		~Bullet() = default;
	};

	class BulletMoveSystem : public POG::Core::System
	{
	public:
		BulletMoveSystem(POG::Core::ECSManager& ecsManager)
			: System::System(ecsManager)
		{
		}

		static POG::Core::Signature GetSignature(POG::Core::ECSManager& ecsManager);

		void Update(float dt);
	};
}

