#pragma once

#include "Debug/Log/Log.h"
#include "Application.h"

extern PEngine::Application* PEngine::CreateApplication();

int main(int argc, char** argv)
{
	PEngine::Log::Init();

	auto app = PEngine::CreateApplication();

	app->PreInit();
	app->Init();
	app->PostInit();

	app->Run();

	delete app;
}