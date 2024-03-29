#pragma once

#include "POGEditorEvents.h"

#include "POGCore.h"
#include "POGDebug.h"
#include "POGLog.h"
#include "POGGraphics.h"

typedef POG::Core::IApplication* (__cdecl* CreateClientApplication)();

namespace POG::Editor
{
	class POGEditor : public POG::Core::Application
	{
	public:
		static POGEditor& GetInstance();

		POGEditor();

		virtual ~POGEditor();

		void Exit() override;

		void Init() override;

		void TryUpdate(float timeBetweenLoops) override;
		void TryFrame(float timeBetweenLoops) override;

		void Input(Core::InputPackage& inputPackage, float dt) override;
		void Update(float dt) override;
		void Frame(float alpha) override;

		Core::IApplication& GetClientApplication() { return *clientApplication; }

		std::string GetClientWorkspaceDirectory() const { return clientWorkspaceDirectory; }
		void SetClientWorkspaceDirectory(std::string clientWorkspaceDirectory) { this->clientWorkspaceDirectory = clientWorkspaceDirectory; }

		bool IsClientFocused() const { return isClientFocused; }
		bool IsClientPaused() const { return isClientPaused; }
		bool IsClientLoaded() const { return clientApplication; }

	private:
		static POGEditor* Instance;

		HINSTANCE exampleDll;
		CreateClientApplication createClientApplication;

		Core::IApplication* clientApplication;

		std::string clientWorkspaceDirectory;

		bool isClientFocused;
		bool isClientPaused;
		bool wasCursorEnabled;

		void OnInputEvent(Core::InputEvent& e);
		void OnKeyEvent(Core::RawKeyEvent& e);
		void OnMouseButtonEvent(Core::RawMouseButtonEvent& e);
		void OnMouseMoveEvent(Core::RawMouseMoveEvent& e);

		void OnClientFocusedEvent(ClientFocusedEvent& e);
		void OnClientPlayEvent(ClientPlayEvent& e);
		void OnClientPauseEvent(ClientPauseEvent& e);
		void OnClientStopEvent(ClientStopEvent& e);

		void LoadClient();
		void UnloadClient();
	};
}