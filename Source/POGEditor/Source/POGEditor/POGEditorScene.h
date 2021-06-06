#pragma once

#include "POGEditorEvents.h"

#include "POGEditor/Gui/Gui.h"

#include "POGCore.h"
#include "POGGraphics.h"

namespace POG::Editor
{
	class POGEditorScene : public POG::Core::Scene
	{
	public:
		POGEditorScene() = default;

		virtual ~POGEditorScene() = default;

		void Init() override;

		void Exit() override;

		void Input(Core::InputPackage& inputPackage, float dt) override;
		void Update(float dt) override;
		void Frame(float alpha) override;

	private:
		Gui gui;

		Graphics::Shader shader;
		Graphics::VertexBuffer vbo;
		Graphics::VertexArray vao;

		Graphics::FrameBuffer clientFBO;
		Graphics::Texture clientTexture;

		void OnClientFocusedEvent(ClientFocusedEvent& e);
		void OnCursorEnabledEvent(Core::CursorEnabledEvent& e);
	};
}

