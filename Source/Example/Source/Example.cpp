#include "ExamplePCH.h"

#include "POGRender.h"

#include "POGCore/Main.h"

namespace POG
{
	class POGApplication : public Core::Application
	{
	public:
		POGApplication()
			: Application::Application("POG")
		{
		}

		void Init() override
		{
			Render::Render::SetContextAddressFunc(GetWindow().GetContextAddressFunc());
		}
	};

	std::unique_ptr<Core::Application> Core::CreateApplication()
	{
		return std::make_unique<POGApplication>();
	}
}