#pragma once

#include "UIProperties.h"

namespace POG::Core
{
	class Control
	{
	public:
		Control();
		Control(Control& parent);
		Control(const Control&) = delete;
		Control(Control&&) = delete;

		virtual ~Control();

		virtual void Draw() = 0;

		template<class T, typename... Args>
		T& AddControl(Args&&... args)
		{
			T* control = new T(std::forward<Args>(args)...);
			children.push_back(control);
			control->parent = this;

			return *control;
		}

		void RemoveControl(Control& control);

	protected:
		Control* parent;
		std::vector<Control*> children;

		int x, y;
		int width, height;

	private:
		Control(Control* parent);
	};
}

