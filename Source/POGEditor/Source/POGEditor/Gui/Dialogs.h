#pragma once

#include <functional>
#include <vector>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace POG::Editor
{
	const int DefaultButtonWidth = 80;

	class ModalDialog
	{
	public:
		ModalDialog(const char* title)
			: title(title)
			, shouldOpen(false)
		{
		}

		void Render();

		bool ShouldOpen() const { return shouldOpen; }
		void Open() { shouldOpen = true; }

	protected:
		virtual void RenderContent() = 0;

	private:
		const char* title;

		bool shouldOpen;
	};

	class ConfirmationDialog : public ModalDialog
	{
	public:
		ConfirmationDialog(const char* message)
			: ModalDialog::ModalDialog("Are you sure?")
			, message(message)
			, buttonNames()
			, buttonActions()
		{
		}

		void AddButton(const char* name, std::function<void()> action = [] {})
		{
			buttonNames.push_back(name);
			buttonActions.push_back(action);
		}

	protected:
		void RenderContent() override;

	private:
		const char* message;

		std::vector<const char*> buttonNames;
		std::vector<std::function<void()>> buttonActions;
	};
}