#pragma once

#include "Layer/Layer.h"

#include "Render/Core/Render.h"
#include "Render/Core/Objects/VertexBuffer.h"
#include "Render/Core/Objects/IndexBuffer.h"
#include "Render/Core/Objects/VertexArray.h"
#include "Render/Core/Shader.h"
#include "Render/Mesh/StaticMeshSet.h"
#include "Render/Material/Material.h"

#include "ECS/Component/Components.h"

namespace Pagoog
{
	class PlayerMoveSystem : public System
	{
	public:
		static Signature GetSignature(ECSCoordinator& coordinator)
		{
			Signature signature;
			signature.set(coordinator.GetComponentType<ECSRigidBody>());
			signature.set(coordinator.GetComponentType<ECSCamera>());

			return signature;
		}

		void InputUpdate(ECSCoordinator& coordinator, float speedX, float speedY, float speedZ);
	};

	class PlayerCameraSystem : public System
	{
	public:
		static Signature GetSignature(ECSCoordinator& coordinator)
		{
			Signature signature;
			signature.set(coordinator.GetComponentType<ECSTransform>());
			signature.set(coordinator.GetComponentType<ECSCamera>());

			return signature;
		}

		void InputUpdate(ECSCoordinator& coordinator, float dt);
	};

	class PlayerInteractSystem : public System
	{
	public:
		static Signature GetSignature(ECSCoordinator& coordinator)
		{
			Signature signature;
			signature.set(coordinator.GetComponentType<ECSTransform>());
			signature.set(coordinator.GetComponentType<ECSCamera>());

			return signature;
		}

		void InputUpdate(ECSCoordinator& coordinator, bool left, bool right, Mesh& mesh, Material& material, RayCastSystem& rayCastSystem);
	};

	class ECSLayer : public Layer
	{
	public:
		ECSLayer();
		virtual ~ECSLayer();

		virtual void Init() override;

		virtual void CollisionsUpdate(float dt) override;
		virtual void Update(float dt) override;
		virtual void FrameUpdate(float alpha) override;

		virtual void HandleEvent(Event& e) override;

		void ActionCallback(InputPackage& inputPackage, float dt);

	private:
		Shared<PlayerMoveSystem> playerMoveSystem;
		Shared<PlayerCameraSystem> playerCameraSystem;
		Shared<PlayerInteractSystem> playerInteractSystem;

		StaticMeshSet meshSet;
		Mesh mesh, mesh2, mesh3, mesh4;

		Material material1;
		Shader shader;

		Entity player;
	};
}