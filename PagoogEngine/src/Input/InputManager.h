#pragma once

#include "InputTypes.h"
#include "InputPackage.h"

#include "Event/InputEvents.h"

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

	struct StateInfo
	{
		int key, action, mods;

		StateInfo(int key, int action, int mods)
			: key(key)
			, action(action)
			, mods(mods)
		{
		}
	};

	class InputManager
	{
	public:
		typedef std::function<void(InputPackage&, float dt)> InputPackageCallback;

		InputManager();
		virtual ~InputManager() = default;

		void Send(float dt);

		bool HandleKeyEvent(KeyEvent& e);

		void AddInputPackageCallback(InputPackageCallback actionCallback);

		void AddAction(std::string name, int key, int action, int mods);
		void AddState(std::string name, int activeKey, int activeAction, int activeMods, int inactiveKey, int inactiveAction, int inactiveMods);

	private:
		std::vector<InputPackageCallback> inputPackageCallbacks;

		std::vector<ActionInfo> actionInfos;
		std::vector<Action> actions;

		std::vector<StateInfo> stateInfosActive;
		std::vector<StateInfo> stateInfosInactive;
		std::vector<State> states;

		InputPackage inputPackage;
	};
}

