#pragma once

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
		static float GetX() { return MouseX; }
		static float GetY() { return MouseY; }
		static float GetPrevX() { return PrevMouseX; }
		static float GetPrevY() { return PrevMouseY; }
		static float GetDeltaX() { return DeltaMouseX; }
		static float GetDeltaY() { return DeltaMouseY; }
		static float NormaliseMouseX();
		static float NormaliseMouseY();

		static bool IsButtonPressed(int button, int mod = POG_MOD_NONE);
		static bool IsButtonReleased(int button, int mod = POG_MOD_NONE);

	private:
		// Stores the most recent mouse button states since last update
		static std::array<int, POG_MAX_MOUSE_VALUE> MouseActions;
		static std::array<int, POG_MAX_MOUSE_VALUE> MouseModifiers;

		static bool ShouldResetMouseMovement;
		static bool MouseHasMoved;
		static float MouseX, MouseY;
		static float PrevMouseX, PrevMouseY;
		static float DeltaMouseX, DeltaMouseY;

		static void Init();

		static void SetXY(float x, float y);

		static void ResetMovement();
		static void ResetDeltas();
		static void ResetButtons();

		static void OnRawMouseMoveEvent(RawMouseMoveEvent& e);
		static void OnRawMouseButtonEvent(RawMouseButtonEvent& e);
	};
}

