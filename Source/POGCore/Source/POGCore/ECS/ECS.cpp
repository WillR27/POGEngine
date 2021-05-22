#include "POGCorePCH.h"
#include "ECS.h"

namespace POG::Core
{
	Signature TransformSystem::GetSignature(ECSManager& ecsManager)
	{
		Signature signature;
		signature.set(ecsManager.GetComponentTypeId<Transform>());
		return signature;
	}

	void TransformSystem::Update(float dt)
	{
		for (EntityId entityId : entityIds)
		{
			auto& transform = ecsManager.GetComponent<Transform>(entityId);
			transform.x += 0.00001f;
			POG_TRACE(transform.x);
		}
	}
}
