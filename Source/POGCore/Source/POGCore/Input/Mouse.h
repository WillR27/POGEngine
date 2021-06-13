#pragma once

#include "POGMaths.h"

#include "InputValues.h"

namespace POG::Core
{
	struct RawMouseMoveEvent;
	struct RawMouseButtonEvent;

	class Mouse
	{
	public:
		friend class Application;
		friend class WindowsWindow;

		static bool HasMouseMoved() { return MouseHasMoved; }

		static Maths::Vec2 GetPos() { return Pos; }
		static float GetX() { return Pos.x; }
		static float GetY() { return Pos.y; }

		static Maths::Vec2 GetPrevPos() { return PrevPos; }
		static float GetPrevX() { return PrevPos.x; }
		static float GetPrevY() { return PrevPos.y; }

		static Maths::Vec2 GetDeltaPos() { return DeltaPos; }
		static float GetDeltaX() { return DeltaPos.x; }
		static float GetDeltaY() { return DeltaPos.y; }

		// Normalises the mouse coords with respect to the window to fit the given range
		static Maths::Vec2 Normalise(Maths::Vec2 min = { -1.0f, -1.0f }, Maths::Vec2 max = { 1.0f, 1.0f });

		// Returns the angle of the mouse cursor relative to the x axis in radians
		// The origin must lie within the range (-1.0f to +1.0f, -1.0f to +1.0f)
		static float AngleFromXAxis(Maths::Vec2 normalisedOrigin = { 0.0f, 0.0f });

		static bool IsButtonPressed(int button, int mod = POG_MOD_NONE);
		static bool IsButtonReleased(int button, int mod = POG_MOD_NONE);

	private:
		// Stores the most recent mouse button states since last update
		static std::array<int, POG_MAX_MOUSE_VALUE> MouseActions;
		static std::array<int, POG_MAX_MOUSE_VALUE> MouseModifiers;

		static bool ShouldResetMouseMovement;
		static bool MouseHasMoved;
		static Maths::Vec2 Pos;
		static Maths::Vec2 PrevPos;
		static Maths::Vec2 DeltaPos;

		static void Init();

		static void SetPos(Maths::Vec2 mousePos);

		static void ResetMovement();
		static void ResetDeltas();
		static void ResetButtons();

		static void OnRawMouseMoveEvent(RawMouseMoveEvent& e);
		static void OnRawMouseButtonEvent(RawMouseButtonEvent& e);
	};
}

