#pragma once

#include "Game/GameObject/Components/Component.h"
#include "Scene/Scene.h"

namespace PEngine
{
	class GameObject
	{
	public:
		GameObject(std::string name = "Game Object");
		virtual ~GameObject();

		template<typename T>
		T& GetComponent()
		{
			return *(static_cast<T*>(components[T::ComponentName()]));
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			T* component = new T(std::forward<Args>(args)...);
			component->gameObject = this;

			std::string componentName = T::ComponentName();
			components[componentName] = static_cast<Component*>(component);

			Scene::AddComponent(static_cast<Component*>(component));

			return *component;
		}

		void SetName(std::string name);
		std::string GetName() const;

		virtual void AddInitialComponents() = 0;

	private:
		std::string name;

		std::unordered_map<std::string, Component*> components;
	};
}