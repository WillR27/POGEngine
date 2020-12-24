#pragma once

#include "Layer/Layer.h"

namespace PEngine
{
	class Scene
	{
	public:
		friend class Application;

		Scene(std::string name);
		~Scene();

		void Update(float dt);
		void FrameUpdate(float dt);

		void AddLayer(Layer* layer);

	private:
		static const Layer* ActiveLayer;

		std::string name;

		std::vector<Layer*> layers;
	};
}

