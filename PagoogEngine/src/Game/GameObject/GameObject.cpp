#include "pgepch.h"
#include "GameObject.h"

namespace PEngine
{
	void GameObject::SetName(std::string name)
	{
		this->name = name;
	}

	std::string GameObject::GetName() const
	{
		return name;
	}
}