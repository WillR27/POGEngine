#include "pgepch.h"
#include "GameObject.h"

namespace PEngine
{
	GameObject::GameObject(std::string name)
		: name(name)
		, components()
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

	BoxCollider& GameObject::GetBoxCollider()
	{
		if (boxCollider == nullptr)
		{
			boxCollider = &GetComponent<BoxCollider>();
		}

		return *boxCollider;
	}

	MeshRenderer& GameObject::GetMeshRenderer()
	{
		if (meshRenderer == nullptr)
		{
			meshRenderer = &GetComponent<MeshRenderer>();
		}

		return *meshRenderer;
	}

	RigidBody& GameObject::GetRigidBody()
	{
		if (rigidBody == nullptr)
		{
			rigidBody = &GetComponent<RigidBody>();
		}

		return *rigidBody;
	}

	Transform& GameObject::GetTransform()
	{
		if (transform == nullptr)
		{
			transform = &GetComponent<Transform>();
		}

		return *transform;
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