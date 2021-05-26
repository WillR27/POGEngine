#pragma once

#include "Input.h"
#include "InputTypes.h"
#include "InputPackage.h"

#include "POGCore/Event/InputEvents.h"

namespace POG::Core
{
	enum class InputType
	{
		Keyboard,
		Mouse,
	};

	struct InputInfo
	{
		InputType type;
		int keyOrButton, action, mods;

		InputInfo(InputType type, int key, int action, int mods = POG_MOD_ANY)
			: type(type)
			, keyOrButton(key)
			, action(action)
			, mods(mods)
		{
		}

		bool operator==(const InputInfo& rhs) const
		{
			return type == rhs.type && keyOrButton == rhs.keyOrButton && action == rhs.action && (mods == POG_MOD_ANY || rhs.mods == POG_MOD_ANY || mods == rhs.mods);
		}
	};

	using InputCallback = std::function<void(InputPackage&, float dt)>;

	class InputManager final
	{
	public:
		InputManager();

		virtual ~InputManager() = default;

		void Dispatch(float dt);

		void HandleKeyEvent(KeyEvent& e);
		void HandleMouseMoveEvent(MouseMoveEvent& e);
		void HandleMouseButtonEvent(MouseButtonEvent& e);

		void AddInputCallback(InputCallback actionCallback);

		void AddAction(std::string name, InputInfo inputInfo);
		void AddState(std::string name, InputInfo activeInputInfo, InputInfo inactiveInputInfo);
		void AddAxis(std::string name, InputInfo activeNegativeInputInfo, InputInfo inactiveNegativeInputInfo, InputInfo activePositiveInputInfo, InputInfo inactivePositiveInputInfo);

	private:
		std::vector<InputCallback> inputPackageCallbacks;

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

