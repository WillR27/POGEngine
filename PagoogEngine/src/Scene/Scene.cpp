#include "pgepch.h"
#include "Scene.h"

#include "Layer/Layer.h"

namespace PEngine
{
	Scene* Scene::ActiveScene = nullptr;

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
			layer->PreInit();
			layer->Init();
			layer->PostInit();
		}
	}

	void Scene::Update(float dt)
	{
		for (Layer* layer : layers)
		{
			layer->PreInputUpdate(dt);
			layer->InputUpdate(dt);
			layer->PostInputUpdate(dt);
		}

		for (Layer* layer : layers)
		{
			layer->CollisionsPreUpdate(dt);
			layer->CollisionsUpdate(dt);
			layer->CollisionsPostUpdate(dt);
		}

		for (Layer* layer : layers)
		{
			layer->PreUpdate(dt);
			layer->Update(dt);
			layer->PostUpdate(dt);
		}
	}

	void Scene::FrameUpdate(float alpha)
	{
		for (Layer* layer : layers)
		{
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