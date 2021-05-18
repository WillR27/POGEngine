#pragma once

#ifdef POG_STANDALONE

#include "POGLog.h"

#include "Application/Application.h"

int main(int argc, char** argv)
{
	POG::Core::Application* app = POG::Core::CreateApplication();

	app->Run();

	delete app;
}

#endif