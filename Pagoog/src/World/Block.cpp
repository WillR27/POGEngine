#include "pgpch.h"
#include "Block.h"

namespace Pagoog
{
	Block::Block()
		: Transform::Transform(PEngine::Vec3(0.0f, 0.0f, 0.0f), glm::angleAxis(glm::radians(90.f), PEngine::Vec3(0.0f, 0.0f, 0.0f)))
		, RigidBody::RigidBody()
		, BoxCollider::BoxCollider()
		, MeshRenderer::MeshRenderer()
	{
	}
}