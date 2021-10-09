#pragma once

#include "Components.h"
#include "ECSManager.h"

namespace POG::Core
{
	class CameraUpdateViewSystem : public System
	{
	public:
		CameraUpdateViewSystem(ECSManager& ecsManager)
			: System::System(ecsManager)
		{
		}

		static Signature GetSignature(ECSManager& ecsManager);

		void UpdateView();
	};

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

	class PhysicsSystem : public System
	{
	public:
		PhysicsSystem(ECSManager& ecsManager)
			: System::System(ecsManager)
		{
		}

		static Signature GetSignature(ECSManager& ecsManager);

		void Update(float dt);
	};

	class SpriteBoxCollider2DRendererSystem : public System
	{
	public:
		SpriteBoxCollider2DRendererSystem(ECSManager& ecsManager)
			: System::System(ecsManager)
		{
		}

		static Signature GetSignature(ECSManager& ecsManager);

		void Frame(float alpha);
	};

	class SpriteRectColliderRendererSystem : public System
	{
	public:
		SpriteRectColliderRendererSystem(ECSManager& ecsManager)
			: System::System(ecsManager)
		{
		}

		static Signature GetSignature(ECSManager& ecsManager);

		void Frame(float alpha);
	};

	class SpriteRendererSystem : public System
	{
	public:
		SpriteRendererSystem(ECSManager& ecsManager)
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

		void Update();
	};
}