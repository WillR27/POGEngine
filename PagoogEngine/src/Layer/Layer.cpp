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
	}

	void Layer::Update()
	{
		inputManager.Send();
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