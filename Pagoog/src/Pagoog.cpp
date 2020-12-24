#include "pgpch.h"

#include "Core/Application.h"
#include "Core/EntryPoint.h"

#include "Layers/WorldLayer.h"

#include "Input/Input.h"

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
			Scene* scene = new Scene("Main Scene");
			scene->AddLayer(new WorldLayer());

			AddScene(scene);

			inputManager.AddAction("Quit", PG_KEY_ESCAPE, PG_KEY_RELEASE, PG_MOD_NONE);
		}

		virtual void ActionCallback(InputPackage& inputPackage, float dt) override
		{
			if (inputPackage.HasActionOccurred("Quit"))
			{
				WindowCloseEvent e;
				EventDispatcher ed(e);
				ed.Dispatch<WindowCloseEvent>(PG_BIND_FN(window->HandleWindowCloseEvent));
			}
		}
	};
}

PEngine::Application* PEngine::CreateApplication()
{
	return new Pagoog::PagoogApplication();
}