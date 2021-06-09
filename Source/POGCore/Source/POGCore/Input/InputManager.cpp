#include "POGCorePCH.h"
#include "InputManager.h"

#include <GLFW/glfw3.h>

namespace POG::Core
{
	InputManager::InputManager(bool setEventsToHandled)
		: actions()
		, setEventsToHandled(setEventsToHandled)
	{
	}

	void InputManager::Dispatch(float dt)
	{
		for (State& state : states)
		{
			if (state.IsOn())
			{
				inputPackage.AddState(state);
			}
		}

		for (Axis& axis : axes)
		{
			if (axis.GetValue() != 0)
			{
				inputPackage.AddAxis(axis);
			}
		}

		for (InputCallback inputPackageCallback : inputPackageCallbacks)
		{
			inputPackageCallback(inputPackage, dt);
		}

		inputPackage.Clear();
	}

	void InputManager::OnKeyEvent(KeyEvent& e)
	{
		InputInfo eventInputInfo(InputType::Keyboard, e.key, e.action, e.mods);
		bool handled = false;

		// Actions
		for (int i = 0; i < actions.size(); i++)
		{
			InputInfo inputInfo = actionInfos[i];
			if (inputInfo == eventInputInfo)
			{
				inputPackage.AddAction(actions[i]);
				handled = true;
			}
		}

		// States
		for (int i = 0; i < states.size(); i++)
		{
			InputInfo inputInfoActive = stateInfosActive[i];
			if (inputInfoActive == eventInputInfo)
			{
				states[i].SetState(true);
				handled = true;
			}
			else
			{
				InputInfo inputInfoInactive = stateInfosInactive[i];
				if (inputInfoInactive == eventInputInfo)
				{
					states[i].SetState(false);
					handled = true;
				}
			}
		}

		// Axes
		for (int i = 0; i < axes.size(); i++)
		{
			int axisValue = axes[i].GetValue();

			InputInfo inputInfoActiveNegative = axisInfosActiveNegative[i];
			if (inputInfoActiveNegative == eventInputInfo)
			{
				if (axisValue > -1)
				{
					axisValue -= 1;
				}
				handled = true;
			}
			else
			{
				InputInfo inputInfoInactiveNegative = axisInfosInactiveNegative[i];
				if (inputInfoInactiveNegative == eventInputInfo)
				{
					if (axisValue < 1)
					{
						axisValue += 1;
					}
					handled = true;
				}
			}

			InputInfo inputInfoActivePositive = axisInfosActivePositive[i];
			if (inputInfoActivePositive == eventInputInfo)
			{
				if (axisValue < 1)
				{
					axisValue += 1;
				}
				handled = true;
			}
			else
			{
				InputInfo inputInfoInactivePositive = axisInfosInactivePositive[i];
				if (inputInfoInactivePositive == eventInputInfo)
				{
					if (axisValue > -1)
					{
						axisValue -= 1;
					}
					handled = true;
				}
			}

			axes[i].SetValue(axisValue);
		}

		if (setEventsToHandled && handled)
		{
			e.SetHandled();
		}
	}

	void InputManager::OnMouseMoveEvent(MouseMoveEvent& e)
	{
		inputPackage.SetMouseMoved();

		if (setEventsToHandled)
		{
			e.SetHandled();
		}
	}

	void InputManager::OnMouseButtonEvent(MouseButtonEvent& e)
	{
		InputInfo eventInputInfo(InputType::Mouse, e.button, e.action, e.mods); // TODO: Merge with key inputs as they are the same?
		bool handled = false;

		// Actions
		for (int i = 0; i < actions.size(); i++)
		{
			InputInfo inputInfo = actionInfos[i];
			if (inputInfo == eventInputInfo)
			{
				inputPackage.AddAction(actions[i]);
				handled = true;
			}
		}

		// States
		for (int i = 0; i < states.size(); i++)
		{
			InputInfo inputInfoActive = stateInfosActive[i];
			if (inputInfoActive == eventInputInfo)
			{
				states[i].SetState(true);
				handled = true;
			}
			else
			{
				InputInfo inputInfoInactive = stateInfosInactive[i];
				if (inputInfoInactive == eventInputInfo)
				{
					states[i].SetState(false);
					handled = true;
				}
			}
		}

		// Axes
		for (int i = 0; i < axes.size(); i++)
		{
			int axisValue = axes[i].GetValue();

			InputInfo inputInfoActiveNegative = axisInfosActiveNegative[i];
			if (inputInfoActiveNegative == eventInputInfo)
			{
				if (axisValue > -1)
				{
					axisValue -= 1;
				}
				handled = true;
			}
			else
			{
				InputInfo inputInfoInactiveNegative = axisInfosInactiveNegative[i];
				if (inputInfoInactiveNegative == eventInputInfo)
				{
					if (axisValue < 1)
					{
						axisValue += 1;
					}
					handled = true;
				}
			}

			InputInfo inputInfoActivePositive = axisInfosActivePositive[i];
			if (inputInfoActivePositive == eventInputInfo)
			{
				if (axisValue < 1)
				{
					axisValue += 1;
				}
				handled = true;
			}
			else
			{
				InputInfo inputInfoInactivePositive = axisInfosInactivePositive[i];
				if (inputInfoInactivePositive == eventInputInfo)
				{
					if (axisValue > -1)
					{
						axisValue -= 1;
					}
					handled = true;
				}
			}

			axes[i].SetValue(axisValue);
		}

		if (setEventsToHandled && handled)
		{
			e.SetHandled();
		}
	}

	void InputManager::AddInputCallback(InputCallback inputCallback)
	{
		inputPackageCallbacks.push_back(inputCallback);
	}

	void InputManager::AddAction(std::string name, InputInfo inputInfo)
	{
		actionInfos.push_back(inputInfo);
		actions.emplace_back(name);
	}

	void InputManager::AddState(std::string name, InputInfo activeInputInfo, InputInfo inactiveInputInfo)
	{
		stateInfosActive.push_back(activeInputInfo);
		stateInfosInactive.push_back(inactiveInputInfo);
		states.emplace_back(name);
	}

	void InputManager::AddAxis(std::string name, InputInfo activeNegativeInputInfo, InputInfo inactiveNegativeInputInfo, InputInfo activePositiveInputInfo, InputInfo inactivePositiveInputInfo)
	{
		axisInfosActiveNegative.push_back(activeNegativeInputInfo);
		axisInfosInactiveNegative.push_back(inactiveNegativeInputInfo);
		axisInfosActivePositive.push_back(activePositiveInputInfo);
		axisInfosInactivePositive.push_back(inactivePositiveInputInfo);
		axes.emplace_back(name);
	}
}