#include "pgepch.h"
#include "Scene.h"

#include "Layer/Layer.h"
#include "Game/GameObject/GameObject.h"
#include "Game/GameObject/Components/Components.h"

namespace PEngine
{
	Scene* Scene::ActiveScene = nullptr;

	void Scene::_AddGameObject(GameObject* gameObject)
	{
		Layer::ActiveLayer->gameObjects		.push_back(gameObject);
		Layer::ActiveLayer->boxColliders	.push_back(gameObject->GetComponentNoWarning<BoxCollider>());
		Layer::ActiveLayer->cameras			.push_back(gameObject->GetComponentNoWarning<Camera>());
		Layer::ActiveLayer->meshRenderers	.push_back(gameObject->GetComponentNoWarning<MeshRenderer>());
		Layer::ActiveLayer->rigidBodies		.push_back(gameObject->GetComponentNoWarning<RigidBody>());
		Layer::ActiveLayer->transforms		.push_back(gameObject->GetComponentNoWarning<Transform>());

		(*gameObject->exists) = true;
		gameObject->Init();
	}

	void Scene::RemoveGameObject(GameObject* gameObject)
	{
		int index = IndexOf(Layer::ActiveLayer->gameObjects, gameObject);

		if (index != -1)
		{
			Layer::ActiveLayer->gameObjects.erase(Layer::ActiveLayer->gameObjects.begin() + index);
			Layer::ActiveLayer->boxColliders.erase(Layer::ActiveLayer->boxColliders.begin() + index);
			Layer::ActiveLayer->cameras.erase(Layer::ActiveLayer->cameras.begin() + index);
			Layer::ActiveLayer->meshRenderers.erase(Layer::ActiveLayer->meshRenderers.begin() + index);
			Layer::ActiveLayer->rigidBodies.erase(Layer::ActiveLayer->rigidBodies.begin() + index);
			Layer::ActiveLayer->transforms.erase(Layer::ActiveLayer->transforms.begin() + index);
		}

		(*gameObject->exists) = false;
	}

	void Scene::DeleteGameObject(GameObject* gameObject)
	{
		RemoveGameObject(gameObject);

		delete gameObject;
	}

	GameObject* Scene::RayCast(Vec3 position, Vec3 direction, const GameObject& objectToIgnore)
	{
		return ActiveScene->_RayCast(position, direction, objectToIgnore);
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
			Layer::ActiveLayer = layer;
			layer->Init();
		}
	}

	void Scene::Update(float dt)
	{
		for (Layer* layer : layers)
		{
			Layer::ActiveLayer = layer;
			layer->InputUpdate(dt);
		}

		for (Layer* layer : layers)
		{
			Layer::ActiveLayer = layer;
			layer->CollisionsPreUpdate(dt);
			layer->CollisionsUpdate(dt);
			layer->CollisionsPostUpdate(dt);
		}

		for (Layer* layer : layers)
		{
			Layer::ActiveLayer = layer;
			layer->PreUpdate(dt);
			layer->Update(dt);
			layer->PostUpdate(dt);
		}
	}

	void Scene::FrameUpdate(float alpha)
	{
		for (Layer* layer : layers)
		{
			Layer::ActiveLayer = layer;
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

	GameObject* Scene::_RayCast(Vec3 position, Vec3 direction, const GameObject& objectToIgnore) const
	{
		const float step = 0.1f;
		const float limit = 100.0f;

		GameObject* hitObject = nullptr;
		float totalDistance = 0.0f;

		Vec3 newPosition = position;

		while (totalDistance < limit && hitObject == nullptr)
		{
			newPosition += direction * step;
			totalDistance += step;

			for (BoxCollider* boxCollider : Layer::ActiveLayer->boxColliders)
			{
				if (boxCollider != nullptr && boxCollider->gameObject != &objectToIgnore)
				{
					if (boxCollider->GetTransformedAABB().IsCollidingWith(newPosition))
					{
						hitObject = boxCollider->gameObject;
					}
				}
			}
		}

		return hitObject;
	}
}