#include "ExamplePCH.h"

#include "POGRender.h"

#include "POGCore/Main.h"

namespace Example
{
	class ExampleApplication : public POG::Core::Application
	{
	public:
		ExampleApplication()
			: Application::Application("POG Example")
		{
		}

		void Init() override
		{
			POG::Render::Render::SetContextAddressFunc(GetWindow().GetContextAddressFunc());

			inputManager.AddAction("Quit", POG::Core::InputInfo(POG::Core::InputType::Keyboard, PG_KEY_ESCAPE, PG_KEY_RELEASE, PG_MOD_ANY));
			inputManager.AddAction("Fullscreen", POG::Core::InputInfo(POG::Core::InputType::Keyboard, PG_KEY_F11, PG_KEY_RELEASE, PG_MOD_ANY));
		}

		void Input(POG::Core::InputPackage& inputPackage, float dt) override
		{
			if (inputPackage.HasActionOccurred("Quit", true))
			{
				Quit();
			}

			if (inputPackage.HasActionOccurred("Fullscreen", true))
			{
				GetWindow().ToggleFullscreen();
			}
		}
	};
}

std::unique_ptr<POG::Core::Application> POG::Core::CreateApplication()
{
	return std::make_unique<Example::ExampleApplication>();
}