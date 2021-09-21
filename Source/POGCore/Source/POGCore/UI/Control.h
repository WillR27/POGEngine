#pragma once

#include "UIProperties.h"

namespace POG::Core
{
	class Control
	{
	public:
		Control();
		Control(const Control&) = delete;
		Control(Control&&) = delete;

		virtual ~Control();

		virtual void Draw() = 0;

		void DrawChildren();

		template<class T, typename... Args>
		T& AddControl(Args&&... args)
		{
			T* control = new T(std::forward<Args>(args)...);
			children.push_back(control);
			control->parent = this;

			return *control;
		}

		void RemoveControl(Control& control);

		Control& GetParent() const { return *parent; }
		void SetParent(Control& parent) { this->parent = &parent; }

		std::vector<Control*>& GetChildren() { return children; }

		int GetX() const { return x; }
		void SetX(int x) { this->x = x; }
		int GetY() const { return y; }
		void SetY(int y) { this->y = y; }

		int GetWindowX() const { return windowX; }
		int GetWindowY() const { return windowY; }

		int GetWidth() const { return width; }
		void SetWidth(int width) { this->width = width; }
		int GetHeight() const { return height; }
		void SetHeight(int height) { this->height = height; }

		int GetActualWidth() const { return actualWidth; }
		int GetActualHeight() const { return actualHeight; }

	protected:
		Control* parent;
		std::vector<Control*> children;

		int x, y;
		int windowX, windowY;
		int width, height;
		int actualWidth, actualHeight;
	};
}

