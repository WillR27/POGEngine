#pragma once

#include <imgui.h>

namespace POG::Editor
{
	const float WindowBorderSize = 0.0f;
	const float WindowPaddingX = 10.0f;
	const float WindowPaddingY = 10.0f;

	const float TabBorderSize = 0.0f;
	const float TabRounding = 0.0f;

	const float FrameBorderSize = 0.0f;
	const float FramePaddingX = 7.0f; 
	const float FramePaddingY = 3.0f;

	const float ScrollbarRounding = 0.0f;

	const float ChildBorderThickness = 0.0f;
	const float ChildRounding = 0.0f;

	const float IndentSpacing = 10.0f;

	const float ItemSpacingRight = WindowPaddingX;
	const float ItemSpacingBottom = WindowPaddingY;

	const float ItemInnerSpacingRight = 5.0f;
	const float ItemInnerSpacingBottom = 5.0f;

	const ImVec4 Transparent(0.00f, 0.00f, 0.00f, 0.000f);

	const ImVec4 LightestGrey(0.50f, 0.50f, 0.50f, 1.00f);
	const ImVec4 LightererGrey(0.42f, 0.42f, 0.42f, 1.00f);
	const ImVec4 LighterGrey(0.33f, 0.33f, 0.33f, 1.00f);
	const ImVec4 DefaultGrey(0.23f, 0.23f, 0.23f, 1.00f);
	const ImVec4 DarkerGrey(0.15f, 0.15f, 0.15f, 1.00f);
	const ImVec4 DarkererGrey(0.10f, 0.10f, 0.10f, 1.00f);
	const ImVec4 DarkestGrey(0.05f, 0.05f, 0.05f, 1.00f);
}