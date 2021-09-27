#include "POGCorePCH.h"
#include "Keyboard.h"

#include "POGCore/Application/Application.h"
#include "POGCore/Event/Events.h"

#include "Input.h"

namespace POG::Core
{
	std::array<int, POG_MAX_KEY_VALUE> Keyboard::KeyActions = std::array<int, POG_MAX_KEY_VALUE>();
	std::array<int, POG_MAX_KEY_VALUE> Keyboard::KeyModifiers = std::array<int, POG_MAX_KEY_VALUE>();

	void Keyboard::Init()
	{
		auto& mainEventBus = Application::GetInstance().GetMainEventBus();
		mainEventBus.Subscribe(OnRawKeyEvent);

		ResetKeys();
	}

	void Keyboard::OnRawKeyEvent(RawKeyEvent& e)
	{
		if (e.key == -1)
		{
			POG_WARN("Ignoring unknown key!");
			return;
		}

		KeyActions[e.key] = e.action;
		KeyModifiers[e.key] = e.mods;

		Input::GlobalInputManager.OnKeyEvent(e);
	}

	bool Keyboard::IsKeyPressed(int key, int mod)
	{
		return KeyActions[key] == POG_INPUT_PRESS && KeyModifiers[key] == mod;
	}

	bool Keyboard::IsKeyReleased(int key, int mod)
	{
		return KeyActions[key] == POG_INPUT_RELEASE && KeyModifiers[key] == mod;
	}

	bool Keyboard::IsKeyRepeated(int key, int mod)
	{
		return KeyActions[key] == POG_INPUT_REPEAT && KeyModifiers[key] == mod;
	}
	
	void Keyboard::ResetKeys()
	{
		for (int i = 0; i < POG_MAX_KEY_VALUE; i++)
		{
			KeyActions[i] = POG_INPUT_NONE;
			KeyModifiers[i] = POG_MOD_NONE;
		}
	}
}