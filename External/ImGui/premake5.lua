createbaseprojectcpp("ImGui", "StaticLib")
	files
	{
		"imgui_impl_opengl3.cpp",
		"imgui_impl_opengl3.h",
		"imgui_impl_glfw.cpp",
		"imgui_impl_glfw.h",
		
		"imconfig.h",
		"imgui.h",
		"imgui.cpp",
		"imgui_demo.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_tables.cpp",
		"imgui_widgets.cpp",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
	}
	
	includedirs
    {
        "../../External/Glad/include",
		"../../External/GLFW/include",
    }