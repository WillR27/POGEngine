#include "pgepch.h"
#include "Scene.h"

namespace PEngine
{
	const Layer* Scene::ActiveLayer = nullptr;

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
			layer->Update(dt);
		}
	}

	void Scene::FrameUpdate(float dt)
	{
		for (Layer* layer : layers)
		{
			ActiveLayer = layer;
			layer->FrameUpdate(dt);
		}
	}

	void Scene::AddLayer(Layer* layer)
	{
		layer->Init();
		layers.push_back(layer);
	}
}