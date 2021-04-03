#pragma once

#include "POGLog.h"

#include "Application/Application.h"

int main(int argc, char** argv)
{
	POG::Log::Log::Init();

	std::unique_ptr<POG::Core::Application> app = POG::Core::CreateApplication();

	app->PreInit();
	app->Init();
	app->PostInit();

	app->Run();
}