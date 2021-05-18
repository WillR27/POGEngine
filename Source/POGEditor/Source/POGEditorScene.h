#pragma once

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

		void Input(Core::InputPackage& inputPackage, float dt) override;

		void Update(float dt) override;

		void Frame(float alpha) override;

		void HandleEvent(Core::Event& e) override;

		void Exit() override;

	private:
		Render::Shader shader;
		Render::VertexBuffer vbo;
		Render::VertexArray vao;

		bool show_demo_window = true;
		bool show_another_window = false;
	};
}

