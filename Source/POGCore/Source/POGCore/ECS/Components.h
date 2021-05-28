#pragma once

#include "POGCore/ECS/Common.h"

#include "POGMaths.h"
#include "POGRender.h"

#include <memory>

namespace POG::Core
{
	struct AttachedCamera
	{
		std::shared_ptr<Render::Camera> camera;
	};

	struct MeshRenderer
	{
		std::shared_ptr<Render::Mesh> mesh = nullptr;
		std::shared_ptr<Render::Material> material = nullptr;
	};

	struct Transform
	{
		Maths::Vec3 position = Maths::Vec3(0.0f, 0.0f, 0.0f);
		Maths::Quat orientation = Maths::Quat(Maths::Vec3(0.0f, 0.0f, 0.0f));
		Maths::Vec3 scale = Maths::Vec3(1.0f, 1.0f, 1.0f);

		Maths::Vec3 prevPosition = Maths::Vec3(0.0f, 0.0f, 0.0f);
		Maths::Quat prevOrientation = Maths::Quat(Maths::Vec3(0.0f, 0.0f, 0.0f));
		Maths::Vec3 prevScale = Maths::Vec3(1.0f, 1.0f, 1.0f);
	};
}