#pragma once

#include <memory>

#include "POGMaths.h"
#include "POGGraphics.h"

#include "POGCore/ECS/Common.h"
#include "POGCore/Graphics/Camera.h"

namespace POG::Core
{
	struct AttachedCamera
	{
		Maths::Vec3 relativePosition = Maths::Vec3(0.0f, 0.0f, 0.0f);
		Maths::Quat relativeOrientation = Maths::Quat(Maths::Vec3(0.0f, 0.0f, 0.0f));

		std::shared_ptr<Core::Camera> camera = nullptr;
	};

	struct MeshRenderer
	{
		std::shared_ptr<Graphics::Mesh> mesh = nullptr;
		std::shared_ptr<Graphics::Material> material = nullptr;
	};

	struct RigidBody
	{
		Maths::Vec3 force = Maths::Vec3(0.0f, 0.0f, 0.0f);
		Maths::Vec3 velocity = Maths::Vec3(0.0f, 0.0f, 0.0f);
		float mass = 1.0f;
		float dragCoef = 1.0f;
	};

	struct Sprite
	{
		static const float PixelsToUnitsRatio;

		Graphics::Texture* texture = nullptr;
		float pixelsToUnitsRatio = PixelsToUnitsRatio;
	};

	using Transform = Maths::Transform;
	
	struct Interpolator
	{
		Transform prevTransform = Transform();
	};

	//////////////////////////////////////////////////////////////
	// COLLIDERS

	struct BoxCollider2D
	{
		Maths::Vec2 min = Maths::Vec2(-0.5f, -0.5f);
		Maths::Vec2 max = Maths::Vec2(0.5f, 0.5f);
	};

	struct RectCollider
	{
		Maths::Vec2 min = Maths::Vec2(-0.5f, -0.5f);
		Maths::Vec2 max = Maths::Vec2(0.5f, 0.5f);
	};

	// COLLIDERS
	//////////////////////////////////////////////////////////////
}