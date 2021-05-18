#include "POGEditorPCH.h"
#include "POGEditorScene.h"

#include "POGEditor.h"

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace POG::Editor
{
	void POGEditorScene::Init()
	{
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
	}
	void POGEditorScene::Input(Core::InputPackage& inputPackage, float dt)
	{
	}
	void POGEditorScene::Update(float dt)
	{
	}
	void POGEditorScene::Frame(float alpha)
	{
		POGEditor& app = static_cast<POGEditor&>(Core::Application::GetInstance());
		//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		//glBindTexture(GL_TEXTURE_2D, tex);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, app.GetWidth(), app.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
		//app.clientApplication->FrameUpdate(alpha);

		float r = ((float)rand() / (RAND_MAX)) + 0;
		float g = ((float)rand() / (RAND_MAX)) + 0;
		float b = ((float)rand() / (RAND_MAX)) + 0;

		//Render::Render::ClearColour(r, g, b, 1.0f);
		//Render::Render::ClearColourBuffer();
		//Render::Render::ClearDepthBuffer();

		//float vertices[] =
		//{
		//	-0.5f, -0.5f, 0.0f,
		//	 0.5f, -0.5f, 0.0f,
		//	 0.0f,  0.5f, 0.0f
		//};

		//vbo.Bind();
		//vbo.SetVertexData(vertices, sizeof(vertices));

		//vao.Bind();
		//vao.SetAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		//shader.Use();

		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		r = ((float)rand() / (RAND_MAX)) + 0;
		g = ((float)rand() / (RAND_MAX)) + 0;
		b = ((float)rand() / (RAND_MAX)) + 0;
		r = 0.5f, g = 0.1f, b = 0.9f;

		Render::Render::ClearColour(r, g, b, 1.0f);
		Render::Render::ClearColourBuffer();
		Render::Render::ClearDepthBuffer();

		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		ImGui::Begin("GameWindow");
		{
			// Using a Child allow to fill all the space of the window.
			// It also alows customization
			ImGui::BeginChild("GameRender");
			// Get the size of the child (i.e. the whole draw size of the windows).
			ImVec2 wsize = ImGui::GetWindowSize();
			// Because I use the texture from OpenGL, I need to invert the V from the UV.
			ImGui::Image((ImTextureID)app.GetClientTexture(), wsize, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::EndChild();
		}
		ImGui::End();


		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void POGEditorScene::HandleEvent(Core::Event& e)
	{
	}

	void POGEditorScene::Exit()
	{
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}