#pragma once

#include "InputManager.h"
#include "InputValues.h"

namespace POG::Core
{
	struct RawKeyEvent;
	struct RawMouseMoveEvent;
	struct RawMouseButtonEvent;

	class Input
	{
		friend class Application;

	public:
		static void Init();

		static bool KeyPressed(int key, int mod = POG_MOD_NONE);
		static bool KeyReleased(int key, int mod = POG_MOD_NONE);
		static bool KeyRepeated(int key, int mod = POG_MOD_NONE);

		static bool HasMouseMoved() { return MouseHasMoved; }
		static float GetMouseX() { return MouseX; }
		static float GetMouseY() { return MouseY; }
		static float GetPrevMouseX() { return PrevMouseX; }
		static float GetPrevMouseY() { return PrevMouseY; }
		static float GetDeltaMouseX() { return DeltaMouseX; }
		static float GetDeltaMouseY() { return DeltaMouseY; }

		static bool MouseButtonPressed(int button, int mod = POG_MOD_NONE);
		static bool MouseButtonReleased(int button, int mod = POG_MOD_NONE);

		static void AddInputCallback(InputCallback inputCallback);

		static void AddAction(std::string name, InputInfo inputInfo);
		static void AddState(std::string name, InputInfo activeInputInfo, InputInfo inactiveInputInfo);
		static void AddAxis(std::string name, InputInfo activeNegativeInputInfo, InputInfo inactiveNegativeInputInfo, InputInfo activePositiveInputInfo, InputInfo inactivePositiveInputInfo);

	private:
		// Stores the most recent key states since last update
		static std::array<int, POG_MAX_KEY_VALUE> KeyActions;
		static std::array<int, POG_MAX_KEY_VALUE> KeyModifiers;

		// Stores the most recent mouse button states since last update
		static std::array<int, POG_MAX_MOUSE_VALUE> MouseActions;
		static std::array<int, POG_MAX_MOUSE_VALUE> MouseModifiers;

		static bool ShouldResetMouseMovement;
		static bool MouseHasMoved;
		static float MouseX, MouseY;
		static float PrevMouseX, PrevMouseY;
		static float DeltaMouseX, DeltaMouseY;

		static InputManager GlobalInputManager;

		static void ResetKeys();

		static void OnKeyEvent(RawKeyEvent& e);

		static void ResetMouseMovement();
		static void ResetMouseDeltas();
		static void SetMouseXY(float x, float y);

		static void ResetMouseButtons();

		static void OnMouseMoveEvent(RawMouseMoveEvent& e);
		static void OnMouseButtonEvent(RawMouseButtonEvent& e);

		static void Dispatch(float dt);
	};
}

