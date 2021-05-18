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

		void HandleEvent(Core::Event& e) override;

		bool IsClientLoaded() const { return clientApplication; }

	private:
		Core::IApplication* clientApplication;

		HINSTANCE exampleDll;
		CreateClientApplication createClientApplication;

		Core::InputManager* clientInputManager;

		void LoadClientApp();
		void UnloadClientApp();
	};
}