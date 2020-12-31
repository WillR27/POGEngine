#include "pgepch.h"
#include "Scene.h"

#include "Layer/Layer.h"
#include "Game/GameObject/GameObject.h"
#include "Game/GameObject/Components/Component.h"
#include "Game/GameObject/Components/BoxCollider.h"
#include "Game/GameObject/Components/MeshRenderer.h"
#include "Game/GameObject/Components/RigidBody.h"
#include "Game/GameObject/Components/Transform.h"

namespace PEngine
{
	Layer* Scene::ActiveLayer = nullptr;

	void Scene::AddGameObject(GameObject* gameObject)
	{
		ActiveLayer->gameObjects.push_back(gameObject);
		ActiveLayer->boxColliders.push_back(nullptr);
		ActiveLayer->meshRenderers.push_back(nullptr);
		ActiveLayer->rigidBodies.push_back(nullptr);
		ActiveLayer->transforms.push_back(nullptr);

		gameObject->AddInitialComponents();
	}

	void Scene::AddComponent(Component* component)
	{
		int index = IndexOf(ActiveLayer->gameObjects, component->gameObject);
		
		if (index != -1)
		{
			if (component->GetComponentName() == BoxCollider::ComponentName())
			{
				ActiveLayer->boxColliders[index] = static_cast<BoxCollider*>(component);
			}
			else if (component->GetComponentName() == MeshRenderer::ComponentName())
			{
				ActiveLayer->meshRenderers[index] = static_cast<MeshRenderer*>(component);
			}
			else if (component->GetComponentName() == RigidBody::ComponentName())
			{
				ActiveLayer->rigidBodies[index] = static_cast<RigidBody*>(component);
			}
			else if (component->GetComponentName() == Transform::ComponentName())
			{
				ActiveLayer->transforms[index] = static_cast<Transform*>(component);
			}
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

			layer->HandleEvent(e);
		}
	}

	void Scene::AddLayer(Layer* layer)
	{
		layers.push_back(layer);
	}
}