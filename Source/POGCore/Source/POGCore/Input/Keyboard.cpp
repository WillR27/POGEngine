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

	bool Keyboard::IsCharacter(int key)
	{
		return key >= 32 && key <= 126;
	}

	char Keyboard::GetCharacter(int key, int mods)
	{
		if (key >= POG_KEY_A && key <= POG_KEY_Z)
		{
			constexpr int capsMods = POG_MOD_CAPS_LOCK | POG_MOD_SHIFT;

			if (!(mods & capsMods))
			{
				return key + 32;
			}
		}
		else if (mods & POG_MOD_SHIFT)
		{
			switch (key)
			{
			case  '`': return '¬';
			case  '1': return '!';
			case  '2': return '"';
			case  '3': return '£';
			case  '4': return '$';
			case  '5': return '%';
			case  '6': return '^';
			case  '7': return '&';
			case  '8': return '*';
			case  '9': return '(';
			case  '0': return ')';
			case  '-': return '_';
			case  '=': return '+';
			case  '[': return '{';
			case  ']': return '}';
			case  ';': return ':';
			case '\'': return '@';
			case  '#': return '~';
			case '\\': return '|';
			case  ',': return '<';
			case  '.': return '>';
			case  '/': return '?';
			}
		}

		return key;
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