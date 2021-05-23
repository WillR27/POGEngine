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

		void TryUpdate(float timeBetweenLoops) override;
		void TryFrame(float timeBetweenLoops) override;

		void Input(Core::InputPackage& inputPackage, float dt) override;
		void Update(float dt) override;
		void Frame(float alpha) override;

		void HandleEvent(Core::Event& e) override;

		void TryLoadClient();
		void TryUnloadClient();

		Core::IApplication& GetClientApplication() { return *clientApplication; }

		bool IsClientFocused() const { return isClientFocused; }
		void SetClientFocused(bool isFocused) { isClientFocused = isFocused; }

		bool IsClientPaused() const { return isClientPaused; }
		void SetClientPaused(bool isPaused) { isClientPaused = isPaused; }

		bool IsClientLoaded() const { return clientApplication; }

	private:
		HINSTANCE exampleDll;
		CreateClientApplication createClientApplication;

		Core::IApplication* clientApplication;

		bool isClientFocused;
		bool isClientPaused;

		bool LookForReservedKeys(Core::KeyEvent& e);
		bool LookForReservedMouseButtons(Core::MouseButtonEvent& e);

		void LoadClient();
		void UnloadClient();
	};
}