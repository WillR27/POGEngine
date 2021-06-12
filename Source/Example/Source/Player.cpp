#include "ExamplePCH.h"
#include "Player.h"

using namespace POG;

namespace Example
{
	Player::Player(Core::EntityInfo entityInfo, Core::ECSManager& ecsManager, float moveSpeed, float sprintMultiplier)
		: Entity::Entity(entityInfo, ecsManager)
		, moveSpeed(moveSpeed)
		, sprintMultiplier(sprintMultiplier)
	{
		SetName("Player");

		AddComponent(Core::AttachedCamera
			{
				.camera = Core::Camera::MainCamera,
			});

		AddComponent(Core::RigidBody
			{
				.force = Maths::Vec3(0.0f, 0.0f, 0.0f),
				.velocity = Maths::Vec3(0.0f, 0.0f, 0.0f),
				.mass = 1.0f,
				.dragCoef = 1.0f
			});

		AddComponent(Core::Transform
			{
				.position = Maths::Vec3(0.0f, 0.0f, -2.0f),
				.orientation = Maths::Quat(Maths::Vec3(0.0f, 0.0f, 0.0f)),
				.scale = Maths::Vec3(1.0f, 1.0f, 1.0f),
			});
	}

	void Player::InputCallback(Core::InputPackage& inputPackage, float dt)
	{
		auto& rigidBody = GetComponent<Core::RigidBody>();
		auto& transform = GetComponent<Core::Transform>();
		
		rigidBody.force.x = inputPackage.GetAxisValue("Horizontal") * 10.0f;
		rigidBody.force.y = inputPackage.GetAxisValue("Vertical") * 10.0f;

		rigidBody.velocity.x = rigidBody.velocity.x > moveSpeed ? moveSpeed : rigidBody.velocity.x < -moveSpeed ? -moveSpeed : rigidBody.velocity.x;
		rigidBody.velocity.y = rigidBody.velocity.y > moveSpeed ? moveSpeed : rigidBody.velocity.y < -moveSpeed ? -moveSpeed : rigidBody.velocity.y;
		rigidBody.velocity.z = 0.0f;
	}
}