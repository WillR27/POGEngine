#include "ExamplePCH.h"
#include "Example.h"

#include <glad/glad.h>

#include "POGCore/Main.h"

#include "POGCore.h"
#include "POGLog.h"
#include "POGGraphics.h"

#include "ExampleScene.h"

using namespace POG;

namespace Example
{
	ExampleApplication::ExampleApplication()
		: Application::Application("POG Example")
	{
	}

	void ExampleApplication::Init()
	{
		SetTargetUpdatesPerSecond(60.0f);
		SetTargetFramesPerSecond(60.0f);

		//SetCursorEnabled(false);

		Core::Scene::SetActiveScene(std::make_shared<ExampleScene>());

		GetInputManager().AddAction("Quit", Core::InputInfo(Core::InputType::Keyboard, POG_KEY_ESCAPE, POG_INPUT_RELEASE, POG_MOD_ANY));
		GetInputManager().AddAction("Fullscreen", Core::InputInfo(Core::InputType::Keyboard, POG_KEY_F11, POG_INPUT_RELEASE, POG_MOD_ANY));

		GetInputManager().AddAction("Left", Core::InputInfo(Core::InputType::Mouse, POG_MOUSE_BUTTON_LEFT, POG_INPUT_RELEASE));
		GetInputManager().AddAction("Right", Core::InputInfo(Core::InputType::Mouse, POG_MOUSE_BUTTON_RIGHT, POG_INPUT_RELEASE));

		GetInputManager().AddAxis("Fly",
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_LEFT_CONTROL, POG_INPUT_PRESS),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_LEFT_CONTROL, POG_INPUT_RELEASE),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_SPACE, POG_INPUT_PRESS),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_SPACE, POG_INPUT_RELEASE));

		GetInputManager().AddAxis("Horizontal",
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_A, POG_INPUT_PRESS),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_A, POG_INPUT_RELEASE),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_D, POG_INPUT_PRESS),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_D, POG_INPUT_RELEASE));
		
		GetInputManager().AddAxis("Vertical",
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_S, POG_INPUT_PRESS),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_S, POG_INPUT_RELEASE),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_W, POG_INPUT_PRESS),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_W, POG_INPUT_RELEASE));
	}

	void ExampleApplication::TryUpdate(float timeBetweenLoops)
	{
		Application::TryUpdate(timeBetweenLoops);
	}

	void ExampleApplication::TryFrame(float timeBetweenLoops)
	{
		Application::TryFrame(timeBetweenLoops);
	}

	void ExampleApplication::Input(Core::InputPackage& inputPackage, float dt)
	{
		if (inputPackage.HasActionOccurred("Quit", true))
		{
			Exit();
		}

		if (inputPackage.HasActionOccurred("Fullscreen", true))
		{
			ToggleFullscreen();
		}
	}

	void ExampleApplication::Update(float dt)
	{
		Application::Update(dt);
	}

	void ExampleApplication::Frame(float alpha)
	{
		Application::Frame(alpha);
	}
}

Core::Application* Core::CreateApplication()
{
	return new Example::ExampleApplication();
}