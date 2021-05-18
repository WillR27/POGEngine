#pragma once

#include "POGCore.h"
#include "POGDebug.h"
#include "POGLog.h"
#include "POGRender.h"

typedef POG::Core::IApplication* (__cdecl* CreateClientApplication)();

namespace POG::Editor
{
	class POGEditor : public POG::Core::Application
	{
	public:
		POGEditor();

		virtual ~POGEditor();

		void Exit() override;

		void Init() override;

		void Input(Core::InputPackage& inputPackage, float dt) override;

		void Update(float dt) override;

		void Frame(float alpha) override;

		unsigned int GetClientTexture() const { return clientTexture; }

	private:
		static Core::IApplication* clientApplication;

		HINSTANCE exampleDll;
		CreateClientApplication createClientApplication;

		unsigned int clientFBO;
		unsigned int clientTexture;
	};
}