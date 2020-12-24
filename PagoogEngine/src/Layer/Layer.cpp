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

	void Layer::CollisionsUpdate(float dt)
	{
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

	void Layer::PreFrameUpdate(float dt)
	{
	}

	void Layer::PostFrameUpdate(float dt)
	{
		for (MeshRenderer* meshRenderer : meshRenderers)
		{
			meshRenderer->Render(dt);
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