#include "pgepch.h"
#include "Scene.h"

namespace PEngine
{
	Layer* Scene::ActiveLayer = nullptr;

	void Scene::AddGameObject(GameObject* gameObject)
	{
		ActiveLayer->gameObjects.push_back(gameObject);

		MeshRenderer* meshRenderer = dynamic_cast<MeshRenderer*>(gameObject);
		if (meshRenderer != nullptr)
		{
			ActiveLayer->meshRenderers.push_back(meshRenderer);
		}

		RigidBody* rigidBody = dynamic_cast<RigidBody*>(gameObject);
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

	void Scene::UpdateRigidBody(float dt)
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