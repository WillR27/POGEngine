#include "pgepch.h"
#include "GameObject.h"

namespace PEngine
{
	GameObject::GameObject(std::string name)
		: name(name)
		, components()
		, exists(new bool(false))
		, refCount(new int(1))
		, boxCollider(nullptr)
		, meshRenderer(nullptr)
		, rigidBody(nullptr)
		, transform(nullptr)
	{

	}

	GameObject::~GameObject()
	{
		(*refCount)--;
		if ((*refCount) == 0)
		{
			delete exists;
			delete refCount;
		}

		for (auto componentPair : components)
		{
			delete componentPair.second;
		}
	}

	GameObject::GameObject(const GameObject& gameObject)
		: name(gameObject.name)
		, components()
		, exists(new bool(false))
		, refCount(new int(1))
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

			if      (component->GetComponentName() == BoxCollider::ComponentName())  boxCollider = static_cast<BoxCollider*>(component);
			else if (component->GetComponentName() == MeshRenderer::ComponentName()) meshRenderer = static_cast<MeshRenderer*>(component);
			else if (component->GetComponentName() == RigidBody::ComponentName())    rigidBody = static_cast<RigidBody*>(component);
			else if (component->GetComponentName() == Transform::ComponentName())    transform = static_cast<Transform*>(component);
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

	void GameObject::Init()
	{
	}

	void GameObject::Update(float dt)
	{
	}

	void GameObject::FrameUpdate(float alpha)
	{
	}
}