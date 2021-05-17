#pragma once

#include "POGLog.h"

#include "Application/Application.h"

#if defined(POG_STANDALONE) || defined(POG_EDITOR)

int main(int argc, char** argv)
{
	POG::Log::Log::Init();

	std::unique_ptr<POG::Core::Application> app = POG::Core::CreateApplication();

	app->Run();
}

//m #elif



#endif