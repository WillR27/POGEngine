#include "pgepch.h"
#include "GameObject.h"

namespace PEngine
{
	GameObject::GameObject(std::string name)
		: name(name)
		, components()
	{

	}

	GameObject::~GameObject()
	{
		for (auto componentPair : components)
		{
			delete componentPair.second;
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
}