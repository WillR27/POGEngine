#include "pgepch.h"
#include "Scene.h"

namespace PEngine
{
	Layer* Scene::ActiveLayer = nullptr;

	void Scene::AddGameObject(GameObject* gameObject)
	{
		ActiveLayer->gameObjects.push_back(gameObject);

		BoxCollider* boxCollider = gameObject->To<BoxCollider>();
		if (boxCollider != nullptr)
		{
			ActiveLayer->boxColliders.push_back(boxCollider);
		}

		MeshRenderer* meshRenderer = gameObject->To<MeshRenderer>();
		if (meshRenderer != nullptr)
		{
			ActiveLayer->meshRenderers.push_back(meshRenderer);
		}

		RigidBody* rigidBody = gameObject->To<RigidBody>();
		if (rigidBody != nullptr)
		{
			ActiveLayer->rigidBodies.push_back(rigidBody);
		}
	}

	Scene::Scene(std::string name)
		: name(name)
	{
	}

	Scene::~Scene()
	{
		for (Layer* layer : layers)
		{
			delete layer;
		}
	}

	void Scene::Init()
	{
		for (Layer* layer : layers)
		{
			ActiveLayer = layer;
			layer->Init();
		}
	}

	void Scene::Update(float dt)
	{
		for (Layer* layer : layers)
		{
			ActiveLayer = layer;
			layer->InputUpdate(dt);
		}

		for (Layer* layer : layers)
		{
			ActiveLayer = layer;
			layer->CollisionsUpdate(dt);
		}

		for (Layer* layer : layers)
		{
			ActiveLayer = layer;
			layer->PreUpdate(dt);
			layer->Update(dt);
			layer->PostUpdate(dt);
		}
	}

	void Scene::FrameUpdate(float dt)
	{
		for (Layer* layer : layers)
		{
			ActiveLayer = layer;
			layer->PreFrameUpdate(dt);
			layer->FrameUpdate(dt);
			layer->PostFrameUpdate(dt);
		}
	}

	void Scene::HandleEvent(Event & e)
	{
		for (Layer* layer : layers)
		{
			if (e.IsHandled())
			{
				break;
			}

			layer->HandleEvent(e);
		}
	}

	void Scene::AddLayer(Layer* layer)
	{
		layers.push_back(layer);
	}
}