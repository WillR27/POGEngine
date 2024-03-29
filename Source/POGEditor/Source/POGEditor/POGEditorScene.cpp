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

		Core::Application::GetInstance().GetMainEventBus().Subscribe(&POGEditorScene::OnCursorEnabledEvent, this);
		Core::Application::GetInstance().GetMainEventBus().Subscribe(&POGEditorScene::OnClientFocusedEvent, this);
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
		POGEditor& pogEditor = static_cast<POGEditor&>(Core::Application::GetInstance());

		Graphics::BindDefaultFrameBuffer();

		Graphics::ClearColour(0.5f, 0.1f, 0.9f, 1.0f);
		Graphics::ClearColourBuffer();
		Graphics::ClearDepthBuffer();

		gui.SetScene(pogEditor.IsClientLoaded() ? &pogEditor.GetClientApplication().GetActiveScene() : nullptr);
		gui.Frame();
		gui.Dockspace();
		gui.EntitiesPanel();
		gui.PropertiesPanel();
		gui.AssetsPanel();
		gui.MainMenu();
		gui.ShowModalDialogs();
		gui.GameWindow(clientTexture);
		gui.ApplyChanges();
		gui.Render();

		// Setup the fbo for the client app to render to
		clientFBO.Bind();
		clientTexture.SetData(0, pogEditor.GetWidth(), pogEditor.GetHeight());

		if (!pogEditor.IsClientLoaded())
		{
			Graphics::ClearColour(0.5f, 0.1f, 0.9f, 1.0f);
			Graphics::ClearColourBuffer();
			Graphics::ClearDepthBuffer();
		}
	}

	void POGEditorScene::OnClientFocusedEvent(ClientFocusedEvent& e)
	{
		gui.SetClientWindowFocused(e.isClientFocused);
	}

	void POGEditorScene::OnCursorEnabledEvent(Core::CursorEnabledEvent& e)
	{
		gui.SetCursorEnabled(e.isCursorEnabled);
	}
}