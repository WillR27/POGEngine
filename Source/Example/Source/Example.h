#pragma once

#include "POGCore.h"
#include "POGGraphics.h"

namespace Example
{
	class ExampleScene : public POG::Core::Scene
	{
	public:
		ExampleScene() = default;

		virtual ~ExampleScene() = default;

		void Init() override;

		void Exit() override;

		void Input(POG::Core::InputPackage& inputPackage, float dt) override;
		void Update(float dt) override;
		void Frame(float alpha) override;

	private:
		POG::Graphics::Shader shader;
		POG::Graphics::VertexBuffer vbo;
		POG::Graphics::VertexArray vao;

		std::shared_ptr<POG::Graphics::Shader> meshShader;
		std::shared_ptr<POG::Graphics::Mesh> mesh;
		std::shared_ptr<POG::Graphics::Material> material;

		POG::Core::Entity player;
		POG::Core::Entity square;
		POG::Core::Entity child;

		bool flip;
	};

	class ExampleApplication : public POG::Core::Application
	{
	public:
		ExampleApplication();

		void Init() override;

		void TryUpdate(float timeBetweenLoops) override;
		void TryFrame(float timeBetweenLoops) override;

		void Input(POG::Core::InputPackage& inputPackage, float dt) override;
		void Update(float dt) override;
		void Frame(float alpha) override;
	};
}