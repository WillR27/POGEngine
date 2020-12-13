#pragma once

#include "Debug/Log/Log.h"
#include "Application.h"

extern PEngine::Application* PEngine::CreateApplication();

int main(int argc, char** argv)
{
	PEngine::Log::Init();

	auto app = PEngine::CreateApplication();

	app->Init();

	app->Run();

	delete app;
}