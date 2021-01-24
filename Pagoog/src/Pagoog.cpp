#include "pgpch.h"

#include "Core/Application.h"
#include "Core/EntryPoint.h"
#include "Input/Input.h"
#include "Scenes/WorldScene/WorldScene.h"

namespace Pagoog
{
	class PagoogApplication : public PEngine::Application
	{
	public:
		PagoogApplication() 
			: Application()
		{
		}

		~PagoogApplication()
		{
		}

		virtual void Init() override
		{
			AddScene(new WorldScene());

			inputManager.AddAction("Quit", InputInfo(InputType::Keyboard, PG_KEY_ESCAPE, PG_KEY_RELEASE, PG_MOD_ANY));
			inputManager.AddAction("Fullscreen", InputInfo(InputType::Keyboard, PG_KEY_F11, PG_KEY_RELEASE, PG_MOD_ANY));
		}

		virtual void InputCallback(InputPackage& inputPackage, float dt) override
		{
			if (inputPackage.HasActionOccurred("Quit"))
			{
				WindowCloseEvent e;
				EventDispatcher ed(e);
				ed.Dispatch<WindowCloseEvent>(PG_BIND_FN(window->HandleWindowCloseEvent));
			}

			if (inputPackage.HasActionOccurred("Fullscreen"))
			{
				window->ToggleFullscreen();
			}
		}
	};
}

PEngine::Application* PEngine::CreateApplication()
{
	return new Pagoog::PagoogApplication();
}