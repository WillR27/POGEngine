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

		Graphics::LoadFont("Arial", "F:\\arial.ttf");
		Graphics::SetFont("Arial");

		Core::Scene::SetActiveScene(std::make_shared<ExampleScene>());

		Core::Input::AddAction("Quit", Core::InputInfo(Core::InputType::Keyboard, POG_KEY_ESCAPE, POG_INPUT_RELEASE, POG_MOD_ANY));
		Core::Input::AddAction("Fullscreen", Core::InputInfo(Core::InputType::Keyboard, POG_KEY_F11, POG_INPUT_RELEASE, POG_MOD_ANY));

		Core::Input::AddAction("Left", Core::InputInfo(Core::InputType::Mouse, POG_MOUSE_BUTTON_LEFT, POG_INPUT_RELEASE));
		Core::Input::AddAction("Right", Core::InputInfo(Core::InputType::Mouse, POG_MOUSE_BUTTON_RIGHT, POG_INPUT_RELEASE));

		Core::Input::AddAxis("Fly",
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_LEFT_CONTROL, POG_INPUT_PRESS),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_LEFT_CONTROL, POG_INPUT_RELEASE),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_SPACE, POG_INPUT_PRESS),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_SPACE, POG_INPUT_RELEASE));

		Core::Input::AddAxis("Horizontal",
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_A, POG_INPUT_PRESS),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_A, POG_INPUT_RELEASE),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_D, POG_INPUT_PRESS),
			Core::InputInfo(Core::InputType::Keyboard, POG_KEY_D, POG_INPUT_RELEASE));
		
		Core::Input::AddAxis("Vertical",
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