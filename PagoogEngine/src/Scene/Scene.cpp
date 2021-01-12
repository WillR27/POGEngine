#include "pgepch.h"
#include "Scene.h"

#include "Layer/Layer.h"
#include "Game/GameObject/GameObject.h"
#include "Game/GameObject/Components/Components.h"

namespace PEngine
{
	Layer* Scene::ActiveLayer = nullptr;

	void Scene::AddGameObject(GameObject* gameObject)
	{
		ActiveLayer->gameObjects.push_back(gameObject);
		ActiveLayer->boxColliders.push_back(gameObject->GetComponent<BoxCollider>(false));
		ActiveLayer->cameras.push_back(gameObject->GetComponent<Camera>(false));
		ActiveLayer->meshRenderers.push_back(gameObject->GetComponent<MeshRenderer>(false));
		ActiveLayer->rigidBodies.push_back(gameObject->GetComponent<RigidBody>(false));
		ActiveLayer->transforms.push_back(gameObject->GetComponent<Transform>(false));

		gameObject->inScene = true;
		gameObject->Init();
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
			layer->CollisionsPreUpdate(dt);
			layer->CollisionsUpdate(dt);
			layer->CollisionsPostUpdate(dt);
		}

		for (Layer* layer : layers)
		{
			ActiveLayer = layer;
			layer->PreUpdate(dt);
			layer->Update(dt);
			layer->PostUpdate(dt);
		}
	}

	void Scene::FrameUpdate(float alpha)
	{
		for (Layer* layer : layers)
		{
			ActiveLayer = layer;
			layer->PreFrameUpdate(alpha);
			layer->FrameUpdate(alpha);
			layer->PostFrameUpdate(alpha);
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

			layer->PreHandleEvent(e);
		}
	}

	void Scene::AddLayer(Layer* layer)
	{
		layers.push_back(layer);
	}
}