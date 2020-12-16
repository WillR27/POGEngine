#pragma once

#include "Event/InputEvents.h"
#include "InputTypes.h"

namespace PEngine
{
	struct ActionInfo
	{
		int key, action, mods;

		ActionInfo(int key, int action, int mods)
			: key(key)
			, action(action)
			, mods(mods)
		{
		}
	};

	class InputManager
	{
	public:
		typedef std::function<void(std::vector<Action>&)> ActionCallback;

		InputManager();
		virtual ~InputManager() = default;

		bool HandleKeyEvent(KeyEvent& e);

		void AddActionCallback(ActionCallback actionCallback);

		void AddAction(std::string name, int key, int action, int mods);

	private:
		std::vector<ActionCallback> actionCallbacks;

		std::vector<ActionInfo> actionInfos;
		std::vector<Action> actions;
	};
}

