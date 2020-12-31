#include "pgepch.h"
#include "Layer.h"

namespace PEngine
{
	Layer::Layer(const char* name)
		: name(name)
		, inputManager()
		, gameObjects()
		, boxColliders()
		, meshRenderers()
		, rigidBodies()
		, transforms()
	{
	}

	Layer::~Layer()
	{
		for (GameObject* gameObject : gameObjects)
		{
			delete gameObject;
		}
	}

	void Layer::InputUpdate(float dt)
	{
		for (Transform* transform : transforms)
		{
			if (transform != nullptr)
			{
				transform->PreInputUpdateTransform();
			}
		}

		inputManager.Send(dt);
	}

	void Layer::PreUpdate(float dt)
	{

	}

	void Layer::PostUpdate(float dt)
	{
		for (RigidBody* rigidBody : rigidBodies)
		{
			if (rigidBody != nullptr)
			{
				rigidBody->UpdateRigidBody(dt);
			}
		}
	}

	void Layer::CollisionsPreUpdate(float dt)
	{
	}

	void Layer::CollisionsPostUpdate(float dt)
	{
		if (boxColliders.size() > 1)
		{
			for (int i = 0; i < boxColliders.size(); i++)
			{
				for (int j = i + 1; j < boxColliders.size(); j++)
				{
					if (boxColliders[i] != nullptr && boxColliders[j] != nullptr)
					{
						boxColliders[i]->CollideWith(*boxColliders[j]);
					}
				}
			}
		}
	}

	void Layer::PreFrameUpdate(float alpha)
	{
	}

	void Layer::PostFrameUpdate(float alpha)
	{
		for (MeshRenderer* meshRenderer : meshRenderers)
		{
			if (meshRenderer != nullptr)
			{
				meshRenderer->Render(alpha);
			}
		}
	}

	void Layer::HandleEvent(Event& e)
	{
		EventDispatcher ed(e);
		ed.Dispatch<KeyEvent>(PG_BIND_FN(inputManager.HandleKeyEvent));
	}

	const char* Layer::GetName() const
	{
		return name;
	}
}