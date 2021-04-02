project "GLFW"
    location "External/GLFW"
	kind "StaticLib"
	language "C"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

	files
	{
		"External/%{prj.name}/include/GLFW/glfw3.h",
		"External/%{prj.name}/include/GLFW/glfw3native.h",
		"External/%{prj.name}/src/glfw_config.h",
		"External/%{prj.name}/src/context.c",
		"External/%{prj.name}/src/init.c",
		"External/%{prj.name}/src/input.c",
		"External/%{prj.name}/src/monitor.c",
		"External/%{prj.name}/src/vulkan.c",
		"External/%{prj.name}/src/window.c",
	}

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers",
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "Off"

		files
		{
			"External/%{prj.name}/src/win32_init.c",
			"External/%{prj.name}/src/win32_joystick.c",
			"External/%{prj.name}/src/win32_monitor.c",
			"External/%{prj.name}/src/win32_time.c",
			"External/%{prj.name}/src/win32_thread.c",
			"External/%{prj.name}/src/win32_window.c",
			"External/%{prj.name}/src/wgl_context.c",
			"External/%{prj.name}/src/egl_context.c",
			"External/%{prj.name}/src/osmesa_context.c",
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

    filter "configurations:Dist"
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
	    }