#include "pgpch.h"

#include "Core/Application.h"
#include "Core/EntryPoint.h"

#include "Layer/WorldLayer.h"

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
			Application::Init();

			AddLayer(new WorldLayer());
		}
	};
}

PEngine::Application* PEngine::CreateApplication()
{
	return new Pagoog::PagoogApplication();
}