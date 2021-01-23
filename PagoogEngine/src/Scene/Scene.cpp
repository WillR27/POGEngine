#include "pgepch.h"
#include "Scene.h"

#include "Layer/Layer.h"

namespace PEngine
{
	Scene* Scene::ActiveScene = nullptr;

	Scene::Scene(std::string name)
		: name(name)
		, inputManager()
		, ecsManager()
		, transformSystem()
		, physicsSystem()
		, collisionsSystem()
		, cameraUpdateViewSystem()
		, rayCastSystem()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::PreInit()
	{
		ecsManager.Init();

		ecsManager.RegisterComponent<ECSTransform>();
		ecsManager.RegisterComponent<ECSRigidBody>();
		ecsManager.RegisterComponent<ECSBoxCollider>();
		ecsManager.RegisterComponent<ECSMeshRenderer>();
		ecsManager.RegisterComponent<ECSCamera>();

		transformSystem			= ecsManager.RegisterSystem<TransformSystem>();
		physicsSystem			= ecsManager.RegisterSystem<PhysicsSystem>();
		collisionsSystem		= ecsManager.RegisterSystem<CollisionsSystem>();
		cameraUpdateViewSystem	= ecsManager.RegisterSystem<CameraUpdateViewSystem>();
		rayCastSystem			= ecsManager.RegisterSystem<RayCastSystem>();
	}

	void Scene::PostInit()
	{
	}

	void Scene::PreUpdate(float dt)
	{
		inputManager.Send(dt);
	}

	void Scene::PostUpdate(float dt)
	{
		physicsSystem->Update(dt);
		collisionsSystem->Update(dt);
		transformSystem->Update(dt);

		cameraUpdateViewSystem->UpdateView();
	}

	void Scene::PreFrameUpdate(float alpha)
	{
	}

	void Scene::PostFrameUpdate(float alpha)
	{
	}

	void Scene::PreHandleEvent(Event& e)
	{
		EventDispatcher ed(e);
		ed.Dispatch<KeyEvent>(PG_BIND_FN(inputManager.HandleKeyEvent));
		ed.Dispatch<MouseMoveEvent>(PG_BIND_FN(inputManager.HandleMouseMoveEvent));
		ed.Dispatch<MouseButtonEvent>(PG_BIND_FN(inputManager.HandleMouseButtonEvent));

		if (!e.IsHandled())
		{
			HandleEvent(e);
		}
	}

	void Scene::PostHandleEvent(Event& e)
	{
	}
}