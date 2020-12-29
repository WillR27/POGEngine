#include "pgepch.h"
#include "Layer.h"

namespace PEngine
{
	Layer::Layer(const char* name)
		: name(name)
		, inputManager()
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
		inputManager.Send(dt);
	}

	void Layer::PreUpdate(float dt)
	{
	}

	void Layer::PostUpdate(float dt)
	{
		for (RigidBody* rigidBody : rigidBodies)
		{
			rigidBody->UpdateRigidBody(dt);
		}
	}

	void Layer::CollisionsUpdate(float dt)
	{
		if (boxColliders.size() > 1)
		{
			for (int i = 0; i < boxColliders.size(); i++)
			{
				for (int j = i + 1; j < boxColliders.size(); j++)
				{
					boxColliders[i]->CollideWith(*boxColliders[j]);
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
			meshRenderer->Render(alpha);
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