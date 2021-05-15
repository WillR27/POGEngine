#pragma once

#include "InputTypes.h"

namespace POG::Core
{
	class InputPackage
	{
	public:
		friend class InputManager;

		InputPackage();
		~InputPackage() = default;

		bool HasActionOccurred(std::string name, bool remove = false);
		bool IsStateActive(std::string name, bool remove = false);
		int GetAxisValue(std::string name, bool remove = false);
		bool HasMouseMoved(bool remove = false);

		void Clear();

	private:
		std::vector<Action> actions;
		std::vector<State> states;
		std::vector<Axis> axes;

		bool hasMouseMoved;

		void AddAction(Action action);
		void AddState(State state);
		void AddAxis(Axis axis);
		void SetMouseMoved(bool value = true);
	};
}

