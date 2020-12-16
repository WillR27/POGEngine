#pragma once

#include "Event/Event.h"
#include "Input/InputManager.h"

namespace PEngine
{
	class Layer
	{
	public:
		Layer(const char* name);
		virtual ~Layer();

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void HandleEvent(Event& e);

		const char* GetName() const;

	protected:
		const char* name;

		InputManager inputManager;
	};
}

