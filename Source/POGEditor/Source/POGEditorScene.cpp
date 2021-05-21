#include "POGEditorPCH.h"
#include "POGEditorScene.h"

#include "POGEditor.h"

namespace POG::Editor
{
	void POGEditorScene::Init()
	{
		gui.Init();

		const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

		const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

		shader.Init(vertexShaderSource, fragmentShaderSource);

		clientFBO.Bind();
		clientTexture.Bind();
		clientFBO.BindTexture(clientTexture);
	}

	void POGEditorScene::Exit()
	{
		gui.Cleanup();
	}

	void POGEditorScene::Input(Core::InputPackage& inputPackage, float dt)
	{
	}

	void POGEditorScene::Update(float dt)
	{
	}

	void POGEditorScene::Frame(float alpha)
	{
		Render::BindDefaultFrameBuffer();

		Render::ClearColour(0.5f, 0.1f, 0.9f, 1.0f);
		Render::ClearColourBuffer();
		Render::ClearDepthBuffer();

		gui.Frame();
		gui.StartStyle();
		gui.MainMenu();
		gui.Dockspace();
		gui.GameWindow(clientTexture);
		gui.EndStyle();
		gui.Render();

		POGEditor& pogEditor = static_cast<POGEditor&>(Core::Application::GetInstance());
		pogEditor.SetClientFocused(gui.IsClientFocused());
		gui.ShouldLoadClient() ? pogEditor.TryLoadClient() : pogEditor.TryUnloadClient();
		pogEditor.SetClientPaused(gui.IsClientPaused());

		// Setup the fbo for the client app to render to
		clientFBO.Bind();
		clientTexture.SetDimensions(pogEditor.GetWidth(), pogEditor.GetHeight());

		if (!pogEditor.IsClientLoaded())
		{
			Render::ClearColour(0.5f, 0.1f, 0.9f, 1.0f);
			Render::ClearColourBuffer();
			Render::ClearDepthBuffer();
		}
	}

	void POGEditorScene::HandleEvent(Core::Event& e)
	{
	}
}