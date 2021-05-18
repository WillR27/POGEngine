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

		void Input(POG::Core::InputPackage& inputPackage, float dt) override;

		void Update(float dt) override;

		void Frame(float alpha) override;

		void HandleEvent(POG::Core::Event& e) override;

		void Exit() override;

	private:
		POG::Render::Shader shader;
		POG::Render::VertexBuffer vbo;
		POG::Render::VertexArray vao;

		bool flip;
	};

	class ExampleApplication : public POG::Core::Application
	{
	public:
		ExampleApplication();

		void Init() override;

		void Input(POG::Core::InputPackage& inputPackage, float dt) override;

		void HandleEvent(POG::Core::Event& e) override;
	};
}