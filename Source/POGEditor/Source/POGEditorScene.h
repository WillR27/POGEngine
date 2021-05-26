#pragma once

#include "Gui.h"
#include "POGEditorEvents.h"

#include "POGCore.h"
#include "POGRender.h"

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

		Render::Shader shader;
		Render::VertexBuffer vbo;
		Render::VertexArray vao;

		Render::FrameBuffer clientFBO;
		Render::Texture clientTexture;

		void OnClientFocusedEvent(ClientFocusedEvent& e);
		void OnCursorEnabledEvent(Core::CursorEnabledEvent& e);
	};
}

