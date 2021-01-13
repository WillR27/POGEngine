#include "pgepch.h"
#include "Layer.h"

#include "Game/GameObject/GameObject.h"

namespace PEngine
{
	Layer* Layer::ActiveLayer = nullptr;

	Layer::Layer(const char* name)
		: name(name)
		, inputManager()
		, gameObjects()
		, boxColliders()
		, cameras()
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
				transform->PreInputUpdate();
			}
		}

		inputManager.Send(dt);
	}

	void Layer::PreUpdate(float dt)
	{
		for (GameObject* gameObject : gameObjects)
		{
			gameObject->Update(dt);
		}
	}

	void Layer::PostUpdate(float dt)
	{
		for (RigidBody* rigidBody : rigidBodies)
		{
			if (rigidBody != nullptr)
			{
				rigidBody->Update(dt);
			}
		}

		for (Camera* camera : cameras)
		{
			if (camera != nullptr)
			{
				camera->Update(dt);
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
		for (GameObject* gameObject : gameObjects)
		{
			gameObject->FrameUpdate(alpha);
		}
	}

	void Layer::PostFrameUpdate(float alpha)
	{
		for (MeshRenderer* meshRenderer : meshRenderers)
		{
			if (meshRenderer != nullptr)
			{
				meshRenderer->FrameUpdate(alpha);
			}
		}
	}

	void Layer::PreHandleEvent(Event& e)
	{
		EventDispatcher ed(e);
		ed.Dispatch<KeyEvent>(PG_BIND_FN(inputManager.HandleKeyEvent));
		ed.Dispatch<MouseMoveEvent>(PG_BIND_FN(inputManager.HandleMouseMoveEvent));

		if (!e.IsHandled())
		{
			this->HandleEvent(e);
		}
	}

	const char* Layer::GetName() const
	{
		return name;
	}
}