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
		}
	};
}

std::unique_ptr<POG::Core::Application> POG::Core::CreateApplication()
{
	return std::make_unique<Example::ExampleApplication>();
}