#pragma once

#include "POGCore.h"
#include "POGRender.h"

namespace Example
{
	class ExampleScene : public POG::Core::Scene
	{
	public:
		ExampleScene() = default;

		virtual ~ExampleScene() = default;

		void Init() override;

		void Exit() override;

		void Update(float dt) override;

		void FrameUpdate(float alpha) override;

		void HandleEvent(POG::Core::Event& e) override;

	private:
		POG::Render::Shader shader;
		POG::Render::VertexBuffer vbo;
		POG::Render::VertexArray vao;
	};

	class ExampleApplication : public POG::Core::Application
	{
	public:
		ExampleApplication();

		void Init() override;

		void Input(POG::Core::InputPackage& inputPackage, float dt) override;
	};
}