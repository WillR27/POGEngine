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

		static bool HasMouseMoved() { return MouseHasMoved; }
		static float GetMouseX() { return MouseX; }
		static float GetMouseY() { return MouseY; }
		static float GetPrevMouseX() { return PrevMouseX; }
		static float GetPrevMouseY() { return PrevMouseY; }
		static float GetDeltaMouseX() { return DeltaMouseX; }
		static float GetDeltaMouseY() { return DeltaMouseY; }
		static float NormaliseMouseX();
		static float NormaliseMouseY();

		static bool MouseButtonPressed(int button, int mod = POG_MOD_NONE);
		static bool MouseButtonReleased(int button, int mod = POG_MOD_NONE);

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

		static void ResetMouseMovement();
		static void ResetMouseDeltas();
		static void SetMouseXY(float x, float y);

		static void ResetMouseButtons();

		static void OnMouseMoveEvent(RawMouseMoveEvent& e);
		static void OnMouseButtonEvent(RawMouseButtonEvent& e);
	};
}

