#include "POGCorePCH.h"
#include "Input.h"

#include "POGCore/Application/Application.h"
#include "POGCore/Event/Events.h"

namespace POG::Core
{
	InputManager Input::GlobalInputManager(false);

	void Input::AddInputCallback(void(*handler)(InputPackage&, float dt))
	{
		GlobalInputManager.AddInputCallback(Util::Function<void(InputPackage&, float dt)>(handler));
	}

	void Input::AddInputCallback(InputCallback inputCallback)
	{
		GlobalInputManager.AddInputCallback(inputCallback);
	}

	void Input::AddAction(std::string name, InputInfo inputInfo)
	{
		GlobalInputManager.AddAction(name, inputInfo);
	}

	void Input::AddState(std::string name, InputInfo activeInputInfo, InputInfo inactiveInputInfo)
	{
		GlobalInputManager.AddState(name, activeInputInfo, inactiveInputInfo);
	}

	void Input::AddAxis(std::string name, InputInfo activeNegativeInputInfo, InputInfo inactiveNegativeInputInfo, InputInfo activePositiveInputInfo, InputInfo inactivePositiveInputInfo)
	{
		GlobalInputManager.AddAxis(name, activeNegativeInputInfo, inactiveNegativeInputInfo, activePositiveInputInfo, inactivePositiveInputInfo);
	}

	void Input::Dispatch(float dt)
	{
		GlobalInputManager.Dispatch(dt);
	}
}