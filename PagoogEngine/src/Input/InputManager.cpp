#include "pgepch.h"
#include "InputManager.h"

#include <GLFW/glfw3.h>

namespace PEngine
{
	InputManager::InputManager()
		: actions()
	{
	}

	bool InputManager::HandleKeyEvent(KeyEvent& e)
	{
		bool handled = false;

		std::vector<Action> actionsToDispatch;

		for (int i = 0; i < actionInfos.size(); i++)
		{
			ActionInfo actionInfo = actionInfos[i];

			if (e.key == actionInfo.key && e.action == actionInfo.action && e.mods == actionInfo.mods)
			{
				actionsToDispatch.push_back(actions[i]);
				handled = true;
			}
		}

		if (actionsToDispatch.size() != 0)
		{
			for (ActionCallback actionCallback : actionCallbacks)
			{
				actionCallback(actionsToDispatch);
			}
		}

		return handled;
	}

	void InputManager::AddActionCallback(ActionCallback actionCallback)
	{
		actionCallbacks.push_back(actionCallback);
	}

	void InputManager::AddAction(std::string name, int key, int action, int mods)
	{
		actionInfos.emplace_back(key, action, mods);
		actions.emplace_back(name);
	}
}