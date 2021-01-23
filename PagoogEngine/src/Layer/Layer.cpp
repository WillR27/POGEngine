#include "pgepch.h"
#include "Layer.h"

#include "Scene/Camera.h"
#include "Util/Timer.h"

namespace PEngine
{
	Layer::Layer(const char* name)
		: name(name)
	{
	}

	Layer::~Layer()
	{

	}
	void Layer::Init()
	{
	}

	void Layer::InputUpdate(float dt)
	{
	}

	void Layer::Update(float dt)
	{
	}

	void Layer::FrameUpdate(float alpha)
	{
	}

	void Layer::HandleEvent(Event& e)
	{
	}
}