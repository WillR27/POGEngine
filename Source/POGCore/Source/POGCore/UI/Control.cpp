#include "POGCorePCH.h"
#include "Control.h"

#include "Canvas.h"

#include "POGLog.h"
#include "POGMaths.h"

namespace POG::Core
{
	Control::Control()
		: canvas(nullptr)
		, parent(nullptr)
		, children()
		, x(0.0f)
		, y(0.0f)
		, windowX(x)
		, windowY(y)
		, width(100.0f)
		, height(100.0f)
		, actualWidth(width)
		, actualHeight(height)
		, anchor(Core::Anchor::Left | Core::Anchor::Top)
		, eventBus()
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

	void Control::Frame()
	{
		CalculateWindowPos();
		CalculateActualSize();
		Draw();

		for (auto it = children.begin(); it != children.end(); it++)
		{
			(*it)->Frame();
		}
	}

	void Control::CalculateWindowPos()
	{
		SetWindowX(static_cast<int>(x * canvas->GetScaleX()) + parent->GetWindowX());
		SetWindowY(static_cast<int>(y * canvas->GetScaleY()) + parent->GetWindowY());
	}

	void Control::CalculateActualSize()
	{
		SetActualWidth(Maths::Min(width * canvas->GetScaleX(), parent->GetActualWidth() - GetX() * canvas->GetScaleX()));
		SetActualHeight(Maths::Min(height * canvas->GetScaleY(), parent->GetActualHeight() - GetY() * canvas->GetScaleY()));
	}

	void Control::OnParentWidthChanged(float deltaWidth)
	{
		if ((anchor & Anchor::Left) && (anchor & Anchor::Right))
		{
			SetWidth(width - deltaWidth);
		}
		else if ((anchor & Anchor::Right))
		{
			SetX(x - deltaWidth);
		}
		else if ((anchor & Anchor::None))
		{
			SetX(x - deltaWidth / 2.0f);
		}
	}

	void Control::OnParentHeightChanged(float deltaHeight)
	{
		if ((anchor & Anchor::Top) && (anchor & Anchor::Bottom))
		{
			SetHeight(height - deltaHeight);
		}
		else if ((anchor & Anchor::Bottom))
		{
			SetY(y - deltaHeight);
		}
		else if ((anchor & Anchor::None))
		{
			SetY(y - deltaHeight / 2.0f);
		}
	}

	void Control::OnRawMouseButtonEvent(RawMouseButtonEvent& e)
	{
		if (IsMouseOver())
		{
			for (Control* control : children)
			{
				if (e.IsHandled())
				{
					return;
				}

				control->OnRawMouseButtonEvent(e);
			}

			if (e.IsHandled())
			{
				return;
			}

			if (e.action == POG_INPUT_RELEASE)
			{
				eventBus.Publish(MouseReleaseEvent(e.button));
			}

			if (e.action == POG_INPUT_PRESS)
			{
				eventBus.Publish(MousePressEvent(e.button));
			}

			e.SetHandled();
		}
	}

	bool Control::IsMouseOver() const
	{
		float mouseX = Mouse::GetX();
		float mouseY = Mouse::GetY();

		return mouseX >= windowX && mouseX <= windowX + actualWidth && mouseY >= windowY && mouseY <= windowY + actualHeight;
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