#pragma once

#include "Event/Event.h"
#include "Input/InputManager.h"

namespace PEngine
{
	class Layer
	{
	public:
		friend class Scene;

		Layer(const char* name);
		virtual ~Layer();

		virtual void Init() = 0;
		
		void InputUpdate(float dt);
		virtual void Update(float dt) = 0;
		virtual void FrameUpdate(float dt) = 0;

		virtual void HandleEvent(Event& e);

		const char* GetName() const;

	protected:
		const char* name;

		InputManager inputManager;
	};
}

