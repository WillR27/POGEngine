#pragma once

#include "PagoogLog.h"

#include "Application/Application.h"

int main(int argc, char** argv)
{
	Pagoog::Log::Log::Init();

	std::unique_ptr<Pagoog::Core::Application> app = Pagoog::Core::CreateApplication();

	app->PreInit();
	app->Init();
	app->PostInit();

	app->Run();
}