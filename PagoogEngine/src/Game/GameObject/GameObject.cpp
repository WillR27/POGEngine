#include "pgepch.h"
#include "GameObject.h"

namespace PEngine
{
	GameObject::GameObject(std::string name)
		: name(name)
		, components()
		, inScene(false)
		, boxCollider(nullptr)
		, meshRenderer(nullptr)
		, rigidBody(nullptr)
		, transform(nullptr)
	{

	}

	GameObject::~GameObject()
	{
		for (auto componentPair : components)
		{
			delete componentPair.second;
		}
	}

	GameObject::GameObject(const GameObject& gameObject)
		: name(gameObject.name)
		, components()
		, inScene(false)
		, boxCollider(nullptr)
		, meshRenderer(nullptr)
		, rigidBody(nullptr)
		, transform(nullptr)
	{
		for (auto componentPair : gameObject.components)
		{
			Component* component = componentPair.second->Clone();
			component->gameObject = this;
			components[componentPair.first] = component;
		}
	}

	void GameObject::SetName(std::string name)
	{
		this->name = name;
	}

	std::string GameObject::GetName() const
	{
		return name;
	}

	bool GameObject::InScene() const
	{
		return inScene;
	}
}