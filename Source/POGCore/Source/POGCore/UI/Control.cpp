#include "POGCorePCH.h"
#include "Control.h"

#include "POGLog.h"

namespace POG::Core
{
	Control::Control()
		: Control::Control(nullptr)
	{
	}

	Control::Control(Control& parent)
		: Control::Control(&parent)
	{
	}

	Control::Control(Control* parent)
		: parent(parent)
		, children()
		, x(0)
		, y(0)
		, width()
		, height()
	{
	}

	Control::~Control()
	{
		while (children.size() > 0)
		{
			delete children.front();
		}

		if (parent != nullptr)
		{
			parent->children.erase(std::find(parent->children.begin(), parent->children.end(), this));
		}
	}

	void Control::RemoveControl(Control& control)
	{
		auto it = std::find(children.begin(), children.end(), &control);

		if (it == children.end())
		{
			POG_WARN("Tried to remove a control from a canvas that didn't exist!");
		}

		children.erase(it);

		delete& control;
	}
}