#pragma once

#include "InputTypes.h"
#include "InputPackage.h"

#include "Event/InputEvents.h"

namespace PEngine
{
	struct InputInfo
	{
		int key, action, mods;

		InputInfo(int key, int action, int mods)
			: key(key)
			, action(action)
			, mods(mods)
		{
		}

		bool operator==(const InputInfo& rhs) const
		{
			return key == rhs.key && action == rhs.action && mods == rhs.mods;
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

		void AddAction(std::string name, InputInfo inputInfo);
		void AddState(std::string name, InputInfo activeInputInfo, InputInfo inactiveInputInfo);
		void AddAxis(std::string name, InputInfo activeNegativeInputInfo, InputInfo inactiveNegativeInputInfo, InputInfo activePositiveInputInfo, InputInfo inactivePositiveInputInfo);

	private:
		std::vector<InputPackageCallback> inputPackageCallbacks;

		std::vector<InputInfo> actionInfos;
		std::vector<Action> actions;

		std::vector<InputInfo> stateInfosActive;
		std::vector<InputInfo> stateInfosInactive;
		std::vector<State> states;

		std::vector<InputInfo> axisInfosActiveNegative;
		std::vector<InputInfo> axisInfosInactiveNegative;
		std::vector<InputInfo> axisInfosActivePositive;
		std::vector<InputInfo> axisInfosInactivePositive;
		std::vector<Axis> axes;

		InputPackage inputPackage;
	};
}

