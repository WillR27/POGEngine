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
		void AddOrReplaceState(State state);

		void Clear();

		bool IsEmpty() const;

	private:
		std::vector<Action> actions;
		std::vector<State> states;
	};
}

