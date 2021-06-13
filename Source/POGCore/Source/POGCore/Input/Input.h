#pragma once

#include "InputManager.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace POG::Core
{
	class Input
	{
		friend class Application;
		friend class Keyboard;
		friend class Mouse;

	public:
		static void AddInputCallback(void(*handler)(InputPackage&, float dt));

		template<class T>
		static void AddInputCallback(void(T::*handler)(InputPackage&, float dt), T* obj)
		{
			AddInputCallback({ handler, obj });
		}

		static void AddInputCallback(InputCallback inputCallback);

		static void AddAction(std::string name, InputInfo inputInfo);
		static void AddState(std::string name, InputInfo activeInputInfo, InputInfo inactiveInputInfo);
		static void AddAxis(std::string name, InputInfo activeNegativeInputInfo, InputInfo inactiveNegativeInputInfo, InputInfo activePositiveInputInfo, InputInfo inactivePositiveInputInfo);

	private:
		static InputManager GlobalInputManager;

		static void Dispatch(float dt);
	};
}

