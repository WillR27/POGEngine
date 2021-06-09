#pragma once

#include "POGCore/Event/InputEvents.h"

#include "InputPackage.h"
#include "InputTypes.h"
#include "InputValues.h"

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

	using InputCallback = Util::Function<void(InputPackage&, float dt)>;

	class InputManager final
	{
	public:
		InputManager(bool setEventsToHandled = true);

		virtual ~InputManager() = default;

		void Dispatch(float dt);

		void OnKeyEvent(KeyEvent& e);
		void OnMouseMoveEvent(MouseMoveEvent& e);
		void OnMouseButtonEvent(MouseButtonEvent& e);

		void AddInputCallback(InputCallback inputCallback);

		void AddAction(std::string name, InputInfo inputInfo);
		void AddState(std::string name, InputInfo activeInputInfo, InputInfo inactiveInputInfo);
		void AddAxis(std::string name, InputInfo activeNegativeInputInfo, InputInfo inactiveNegativeInputInfo, InputInfo activePositiveInputInfo, InputInfo inactivePositiveInputInfo);

	private:
		bool setEventsToHandled;

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

