#include "PagoogPCH.h"

#include "PagoogCore/Source/Main.h"

#include "PagoogRender/Source/Render.h"

namespace Pagoog
{
	class PagoogApplication : public Core::Application
	{
	public:
		PagoogApplication()
			: Application::Application("Pagoog")
		{
		}

		void Init() override
		{
			Render::Render::SetContextAddressFunc(GetWindow().GetContextAddressFunc());
		}
	};

	std::unique_ptr<Core::Application> Core::CreateApplication()
	{
		return std::make_unique<PagoogApplication>();
	}
}