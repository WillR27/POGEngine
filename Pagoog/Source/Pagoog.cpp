#include "PagoogPCH.h"

#include "PagoogCore/Source/Main.h"

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
		}
	};

	std::unique_ptr<Core::Application> Core::CreateApplication()
	{
		return std::make_unique<PagoogApplication>();
	}
}