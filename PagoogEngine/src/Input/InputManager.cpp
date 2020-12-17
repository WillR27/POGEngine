#include "pgepch.h"
#include "InputManager.h"

#include <GLFW/glfw3.h>

namespace PEngine
{
	InputManager::InputManager()
		: actions()
	{
	}

	void InputManager::Send()
	{
		for (State& state : states)
		{
			if (state.IsOn())
			{
				inputPackage.AddOrReplaceState(state);
			}
		}

		if (!inputPackage.IsEmpty())
		{
			for (InputPackageCallback inputPackageCallback : inputPackageCallbacks)
			{
				inputPackageCallback(inputPackage);
			}
		}

		inputPackage.Clear();
	}

	bool InputManager::HandleKeyEvent(KeyEvent& e)
	{
		for (int i = 0; i < actionInfos.size(); i++)
		{
			ActionInfo actionInfo = actionInfos[i];

			if (e.key == actionInfo.key && e.action == actionInfo.action && e.mods == actionInfo.mods)
			{
				inputPackage.AddAction(actions[i]);
				return true;
			}
		}

		for (int i = 0; i < stateInfosActive.size(); i++)
		{
			StateInfo stateInfoActive = stateInfosActive[i];

			if (e.key == stateInfoActive.key && e.action == stateInfoActive.action && e.mods == stateInfoActive.mods)
			{
				states[i].SetState(true);
				return true;
			}
		}

		for (int i = 0; i < stateInfosInactive.size(); i++)
		{
			StateInfo stateInfoInctive = stateInfosInactive[i];

			if (e.key == stateInfoInctive.key && e.action == stateInfoInctive.action && e.mods == stateInfoInctive.mods)
			{
				states[i].SetState(false);
				return true;
			}
		}

		return false;
	}

	void InputManager::AddInputPackageCallback(InputPackageCallback actionCallback)
	{
		inputPackageCallbacks.push_back(actionCallback);
	}

	void InputManager::AddAction(std::string name, int key, int action, int mods)
	{
		actionInfos.emplace_back(key, action, mods);
		actions.emplace_back(name);
	}

	void InputManager::AddState(std::string name, int activeKey, int activeAction, int activeMods, int inactiveKey, int inactiveAction, int inactiveMods)
	{
		stateInfosActive.emplace_back(activeKey, activeAction, activeMods);
		stateInfosInactive.emplace_back(inactiveKey, inactiveAction, inactiveMods);
		states.emplace_back(name);
	}
}