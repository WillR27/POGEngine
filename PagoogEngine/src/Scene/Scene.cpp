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
		}
	}

	void Scene::Update(float dt)
	{
		//PG_START_SCOPED_PROFILE("Input");
		for (Layer* layer : layers)
		{
			layer->InputUpdate(dt);
		}
		//PG_END_SCOPED_PROFILE();

		//PG_START_SCOPED_PROFILE("Collisions");
		for (Layer* layer : layers)
		{
			layer->CollisionsPreUpdate(dt);
			layer->CollisionsUpdate(dt);
			layer->CollisionsPostUpdate(dt);
		}
		//PG_END_SCOPED_PROFILE();

		//PG_START_SCOPED_PROFILE("Update");
		for (Layer* layer : layers)
		{
			layer->PreUpdate(dt);
			layer->Update(dt);
			layer->PostUpdate(dt);
		}
		//PG_END_SCOPED_PROFILE();
	}

	void Scene::FrameUpdate(float alpha)
	{
		//PG_START_SCOPED_PROFILE("Frame");
		for (Layer* layer : layers)
		{
			layer->PreFrameUpdate(alpha);
			layer->FrameUpdate(alpha);
			layer->PostFrameUpdate(alpha);
		}
		//PG_END_SCOPED_PROFILE();
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