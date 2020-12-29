#pragma once

#include "InputTypes.h"

namespace PEngine
{
	class InputPackage
	{
	public:
		InputPackage() = default;
		~InputPackage() = default;

		bool HasActionOccurred(std::string name, bool remove = true);
		void AddAction(Action action);

		bool IsStateActive(std::string name, bool remove = true);
		void AddState(State state);

		int GetAxisValue(std::string name, bool remove = true);
		void AddAxis(Axis axis);

		void Clear();

		bool IsEmpty() const;

	private:
		std::vector<Action> actions;
		std::vector<State> states;
		std::vector<Axis> axes;
	};
}

