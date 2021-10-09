#pragma once

#include "ControlEvents.h"
#include "UIProperties.h"
#include "POGCore/Input/Input.h"

namespace POG::Core
{
	class Control
	{
	public:
		friend class Canvas;

		Control();
		Control(const Control&) = delete;
		Control(Control&&) = delete;

		virtual ~Control();

		void Frame();

		virtual void Draw() = 0;

		virtual void CalculateWindowPos();
		virtual void CalculateActualSize();

		virtual void OnParentWidthChanged(float deltaWidth);
		virtual void OnParentHeightChanged(float deltaHeight);

		void FindAndSetFocusedControl(RawMouseButtonEvent& e);
		virtual void OnRawMouseButtonEvent(RawMouseButtonEvent& e);
		virtual void OnRawKeyEvent(RawKeyEvent& e);

		bool IsMouseOver() const;

		Canvas& GetCanvas() const { return *canvas; }
		//void SetCanvas(Canvas& canvas) { this->canvas = &canvas; }

		bool IsFocused() const;

		Control& GetParent() const { return *parent; }
		void SetParent(Control& parent) { this->parent = &parent; }

		std::vector<Control*>& GetChildren() { return children; }

		template<class T, typename... Args>
		T& AddControl(Args&&... args)
		{
			T* control = new T(std::forward<Args>(args)...);
			children.push_back(control);
			control->canvas = this->canvas;
			control->parent = this;

			return *control;
		}

		void RemoveControl(Control& control);

		float GetX() const { return x; }
		void SetX(float x) { this->x = x; }
		float GetY() const { return y; }
		void SetY(float y) { this->y = y; }

		float GetWindowX() const { return windowX; }
		void SetWindowX(float windowX) { this->windowX = windowX; }
		float GetWindowY() const { return windowY; }
		void SetWindowY(float windowY) { this->windowY = windowY; }

		float GetWidth() const { return width; }
		void SetWidth(float width) { float deltaWidth = this->width - width; this->width = width; for (Control* control : children) { control->OnParentWidthChanged(deltaWidth); } }
		float GetHeight() const { return height; }
		void SetHeight(float height) { float deltaHeight = this->height - height; this->height = height; for (Control* control : children)  { control->OnParentHeightChanged(deltaHeight); } }

		float GetActualWidth() const { return actualWidth; }
		void SetActualWidth(float actualWidth) { this->actualWidth = actualWidth; }
		float GetActualHeight() const { return actualHeight; }
		void SetActualHeight(float actualHeight) { this->actualHeight = actualHeight; }

		Anchor GetAnchor() const { return anchor; }
		void SetAnchor(Anchor anchor) { this->anchor = anchor; }

		EventBus& GetEventBus() { return eventBus; }

	private:
		Canvas* canvas;
		Control* parent;
		std::vector<Control*> children;

		float x, y;
		float windowX, windowY;
		float width, height;
		float actualWidth, actualHeight;

		Anchor anchor;

		EventBus eventBus;
	};
}

