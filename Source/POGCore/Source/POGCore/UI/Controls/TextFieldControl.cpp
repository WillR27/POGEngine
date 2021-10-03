#include "POGCorePCH.h"
#include "TextFieldControl.h"

#include "POGCore/Application/Application.h"
#include "POGCore/UI/Canvas.h"

#include "POGGraphics.h"

namespace POG::Core
{
	TextFieldControl::TextFieldControl()
		: Control::Control()
		, cursorPos(4)
		, highlightPos(2)
		, textOffset(0)
		, cursorOffset(0)
	{
		GetEventBus().Subscribe(&TextFieldControl::OnMousePressEvent, this);
		GetEventBus().Subscribe(&TextFieldControl::OnKeyPressEvent, this);
		GetEventBus().Subscribe(&TextFieldControl::OnKeyReleaseEvent, this);
		GetEventBus().Subscribe(&TextFieldControl::OnKeyRepeatEvent, this);
	}

	void TextFieldControl::Draw()
	{
		if (GetActualWidth() < 0.0f || GetActualHeight() < 0.0f)
		{
			return;
		}

		characterPositions.clear();
		characterPositions.resize(text.length() + 1);
		characterPositions[0] = 0;
		for (size_t i = 1; i <= text.length(); i++)
		{
			characterPositions[i] = Graphics::GetTextSize(text.substr(0, i), 1.0f).x;
		}

		// Fix the cursor going off the right of the control
		float cursorDif = GetActualWidth() - characterPositions[cursorPos];
		if (cursorDif - textOffset < 0.0f)
		{
			textOffset = cursorDif < 0.0f ? cursorDif : 0.0f;
		}

		// Fix cursor going off the left of the control
		cursorOffset = characterPositions[cursorPos] + textOffset;
		if (cursorOffset < 0.0f)
		{
			textOffset -= cursorOffset;
		}
		cursorOffset = characterPositions[cursorPos] + textOffset;

		Graphics::DrawRectangle(GetWindowX(), (Application::GetInstance().GetHeight() - GetWindowY()) - GetActualHeight(), GetActualWidth(), GetActualHeight(), { 1.0f, 0.9f, 0.3f });

		Graphics::Enable(Graphics::Capability::ScissorTest);
		Graphics::SetScissor(static_cast<int>(GetWindowX()), static_cast<int>((Application::GetInstance().GetHeight() - GetWindowY()) - GetActualHeight()), static_cast<int>(GetActualWidth()), static_cast<int>(GetActualHeight()));

		//if (IsFocused())
		//{
		//	colour = Maths::Vec3(0.7f, 1.0f, 0.2f);

		//	Maths::Vec2i size = Graphics::GetTextSize(text, 1.0f);
		//	Maths::Vec2i size2 = Graphics::GetTextSize("|", 1.0f);
		//	int offset = size.x - static_cast<int>(GetActualWidth()) + size2.x;

		//	Graphics::RenderText(text, static_cast<int>(GetWindowX()) - offset, static_cast<int>((Application::GetInstance().GetHeight() - GetWindowY()) - GetActualHeight()), 1.0f, colour);

		//	Graphics::RenderText("|", static_cast<int>(GetWindowX() + GetActualWidth()) - size2.x, static_cast<int>((Application::GetInstance().GetHeight() - GetWindowY()) - GetActualHeight()), 1.0f, colour);
		//}
		//else
		{
			colour = Maths::Vec3(0.3f, 0.7f, 0.2f);

			if (highlightPos != -1)
			{
				float startX = cursorPos < highlightPos ? characterPositions[cursorPos] : characterPositions[highlightPos];
				float endX = cursorPos > highlightPos ? characterPositions[cursorPos] : characterPositions[highlightPos];
				float width = endX - startX;
				Graphics::DrawRectangle(GetWindowX() + startX + textOffset, (Application::GetInstance().GetHeight() - GetWindowY()) - GetActualHeight(), width, GetActualHeight(), { 1.0f, 1.0f, 1.0f });
			}

			Graphics::RenderText(text, static_cast<int>(GetWindowX() + textOffset), static_cast<int>((Application::GetInstance().GetHeight() - GetWindowY()) - GetActualHeight()), 1.0f, colour);

			Maths::Vec2i size2 = Graphics::GetTextSize("|", 1.0f);
			Graphics::DrawRectangle(GetWindowX() + cursorOffset, (Application::GetInstance().GetHeight() - GetWindowY()) - GetActualHeight(), size2.x / 3.0f, GetActualHeight(), colour);
		}

		Graphics::Disable(Graphics::Capability::ScissorTest);
	}

	void TextFieldControl::CalculateActualSize()
	{
		Maths::Vec2i size = Graphics::GetTextSize(text, 1.0f);
		SetActualWidth(Maths::Min(GetWidth() * GetCanvas().GetScaleX(), Maths::Min(static_cast<float>(size.x), GetParent().GetActualWidth() - GetX() * GetCanvas().GetScaleX())));
		SetActualHeight(Maths::Min(GetHeight() * GetCanvas().GetScaleY(), Maths::Min(static_cast<float>(size.y), GetParent().GetActualHeight() - GetY() * GetCanvas().GetScaleY())));
	}

	void TextFieldControl::OnMousePressEvent(MousePressEvent& e)
	{
		float localMouseX = Mouse::GetX() - GetWindowX();
		float localMouseY = Mouse::GetY() - GetWindowY();

		float smallestDif = 10000.0f;
		for (size_t i = 0; i < characterPositions.size(); i++)
		{
			float dif = abs(localMouseX - characterPositions[i] - textOffset);
			if (dif < smallestDif)
			{
				smallestDif = dif;
				cursorPos = i;
			}
		}
	}

	void TextFieldControl::OnKeyPressEvent(KeyPressEvent& e)
	{
		Type(e.key, e.mods);
	}

	void TextFieldControl::OnKeyReleaseEvent(KeyReleaseEvent& e)
	{
		
	}

	void TextFieldControl::OnKeyRepeatEvent(KeyRepeatEvent& e)
	{
		Type(e.key, e.mods);
	}

	void TextFieldControl::Type(int key, int mods)
	{
		if (key == POG_KEY_LEFT_SHIFT || key == POG_KEY_RIGHT_SHIFT)
		{

		}
		else if (key == POG_KEY_LEFT)
		{
			if (mods | POG_MOD_SHIFT)
			{
				if (highlightPos == -1)
				{
					highlightPos = cursorPos;
				}
			}
			else
			{
				highlightPos = -1;
			}

			cursorPos--;
			cursorPos = cursorPos < 0 ? 0 : cursorPos;
		}
		else if (key == POG_KEY_RIGHT)
		{
			if (mods | POG_MOD_SHIFT)
			{
				if (highlightPos == -1)
				{
					highlightPos = cursorPos;
				}
			}
			else
			{
				highlightPos = -1;
			}

			cursorPos++;
			cursorPos = cursorPos > text.size() ? text.size() : cursorPos;
		}
		else
		{
			if (highlightPos != -1)
			{
				int start = cursorPos > highlightPos ? highlightPos : cursorPos;
				text.erase(start, abs(cursorPos - highlightPos));
				cursorPos = start;
				highlightPos = -1;
			}

			char c = static_cast<char>(key);
			if (cursorPos == text.size())
			{
				text.append(1, c);
				cursorPos++;
			}
			else
			{
				text.insert(cursorPos, 1, c);
			}
		}
	}
}