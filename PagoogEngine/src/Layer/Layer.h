#pragma once

#include "ECS/ECS.h"
#include "Event/Event.h"
#include "Input/InputManager.h"

namespace PEngine
{
	class Layer
	{
	public:
		Layer(const char* name);
		virtual ~Layer();

		virtual void Init();

		virtual void InputUpdate(float dt);
		virtual void Update(float dt);
		virtual void FrameUpdate(float alpha);

		virtual void HandleEvent(Event& e);

		const char* GetName() const { return name; }

	private:
		const char* name;
	};
}

