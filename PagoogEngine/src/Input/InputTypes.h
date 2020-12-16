#pragma once

#include <string>

namespace PEngine
{
	class Action
	{
	public:
		std::string name;

		Action(std::string name) : name(name) {}
		~Action() = default;
	};

	class State
	{
	public:
		State(std::string name) : name(name), on(false) {}
		~State() = default;

		bool IsOn() const { return on; }
		void SetState(bool on) { this->on = on; }

	private:
		std::string name;
		bool on;
	};
}


