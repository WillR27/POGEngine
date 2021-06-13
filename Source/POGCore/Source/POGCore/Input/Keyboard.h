#pragma once

#include "InputValues.h"

namespace POG::Core
{
	struct RawKeyEvent;

	class Keyboard
	{
	public:
		friend class Application;

		static bool KeyPressed(int key, int mod = POG_MOD_NONE);
		static bool KeyReleased(int key, int mod = POG_MOD_NONE);
		static bool KeyRepeated(int key, int mod = POG_MOD_NONE);

	private:
		// Stores the most recent key states since last update
		static std::array<int, POG_MAX_KEY_VALUE> KeyActions;
		static std::array<int, POG_MAX_KEY_VALUE> KeyModifiers;

		static void Init();

		static void ResetKeys();

		static void OnKeyEvent(RawKeyEvent& e);
	};
}
