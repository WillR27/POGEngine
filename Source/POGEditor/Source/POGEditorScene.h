#pragma once

#include "POGCore.h"
#include "POGRender.h"

#include "Gui.h"

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

		void HandleEvent(Core::Event& e) override;

	private:
		Gui gui;

		Render::Shader shader;
		Render::VertexBuffer vbo;
		Render::VertexArray vao;

		Render::FrameBuffer clientFBO;
		Render::Texture clientTexture;
	};
}

