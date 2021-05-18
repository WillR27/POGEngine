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

		InputInfo(InputType type, int key, int action, int mods = PG_MOD_ANY)
			: type(type)
			, keyOrButton(key)
			, action(action)
			, mods(mods)
		{
		}

		bool operator==(const InputInfo& rhs) const
		{
			return type == rhs.type && keyOrButton == rhs.keyOrButton && action == rhs.action && (mods == PG_MOD_ANY || rhs.mods == PG_MOD_ANY || mods == rhs.mods);
		}
	};

	typedef std::function<void(InputPackage&, float dt)> InputCallback;

	class IInputManager
	{
	public:
		virtual void Dispatch(float dt) = 0;

		virtual bool HandleKeyEvent(KeyEvent& e) = 0;
		virtual bool HandleMouseMoveEvent(MouseMoveEvent& e) = 0;
		virtual bool HandleMouseButtonEvent(MouseButtonEvent& e) = 0;

		virtual void AddInputCallback(InputCallback actionCallback) = 0;

		virtual void AddAction(std::string name, InputInfo inputInfo) = 0;
		virtual void AddState(std::string name, InputInfo activeInputInfo, InputInfo inactiveInputInfo) = 0;
		virtual void AddAxis(std::string name, InputInfo activeNegativeInputInfo, InputInfo inactiveNegativeInputInfo, InputInfo activePositiveInputInfo, InputInfo inactivePositiveInputInfo) = 0;
	};

	class InputManager : public IInputManager
	{
	public:
		InputManager();
		virtual ~InputManager() = default;

		void Dispatch(float dt) override;

		bool HandleKeyEvent(KeyEvent& e) override;
		bool HandleMouseMoveEvent(MouseMoveEvent& e) override;
		bool HandleMouseButtonEvent(MouseButtonEvent& e) override;

		void AddInputCallback(InputCallback actionCallback) override;

		void AddAction(std::string name, InputInfo inputInfo) override;
		void AddState(std::string name, InputInfo activeInputInfo, InputInfo inactiveInputInfo) override;
		void AddAxis(std::string name, InputInfo activeNegativeInputInfo, InputInfo inactiveNegativeInputInfo, InputInfo activePositiveInputInfo, InputInfo inactivePositiveInputInfo) override;

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

