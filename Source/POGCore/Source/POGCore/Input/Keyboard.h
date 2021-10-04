#pragma once

#include "InputValues.h"

namespace POG::Core
{
	struct RawKeyEvent;

	class Keyboard
	{
	public:
		friend class Application;

		static bool IsKeyPressed(int key, int mod = POG_MOD_NONE);
		static bool IsKeyReleased(int key, int mod = POG_MOD_NONE);
		static bool IsKeyRepeated(int key, int mod = POG_MOD_NONE);

		static char GetCharacter(int key, int mods);

	private:
		// Stores the most recent key states since last update
		static std::array<int, POG_MAX_KEY_VALUE> KeyActions;
		static std::array<int, POG_MAX_KEY_VALUE> KeyModifiers;

		static void Init();

		static void ResetKeys();

		static void OnRawKeyEvent(RawKeyEvent& e);
	};
}
