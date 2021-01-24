workspace "Pagoog"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"



project "Pagoog"
    location "Pagoog"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "On"

    targetdir ("Builds/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Builds/int/" .. outputdir .. "/%{prj.name}")

    pchheader "pgpch.h"
	pchsource "src/pgpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.hpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "PagoogEngine/src",
        "PagoogEngine/vendor/spdlog/include",
        "PagoogEngine/vendor/glm/glm"
    }

    links
    {
        "PagoogEngine"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {

        }

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers"
	}

    filter "configurations:Debug"
        defines "PG_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "PG_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "PG_DIST"
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
	    }



project "PagoogEngine"
    location "PagoogEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "On"

    targetdir ("Builds/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Builds/int/" .. outputdir .. "/%{prj.name}")

    pchheader "pgepch.h"
	pchsource "src/pgepch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.hpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/glfw/include",
        "%{prj.name}/vendor/glad/include",
        "%{prj.name}/vendor/glm/glm"
    }

    links
    {
        "GLFW",
        "Glad"
	}

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers"
	}

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "PG_DEBUG", "PG_ENABLE_ASSERT" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "PG_RELEASE", "PG_ENABLE_VERIFY" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "PG_DIST" }
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
	    }



project "GLFW"
    location "GLFW"
	kind "StaticLib"
	language "C"

    targetdir ("Builds/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Builds/int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"PagoogEngine/vendor/glfw/include/GLFW/glfw3.h",
		"PagoogEngine/vendor/glfw/include/GLFW/glfw3native.h",
		"PagoogEngine/vendor/glfw/src/glfw_config.h",
		"PagoogEngine/vendor/glfw/src/context.c",
		"PagoogEngine/vendor/glfw/src/init.c",
		"PagoogEngine/vendor/glfw/src/input.c",
		"PagoogEngine/vendor/glfw/src/monitor.c",
		"PagoogEngine/vendor/glfw/src/vulkan.c",
		"PagoogEngine/vendor/glfw/src/window.c"
	}

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers"
	}

	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		files
		{
			"PagoogEngine/vendor/glfw/src/x11_init.c",
			"PagoogEngine/vendor/glfw/src/x11_monitor.c",
			"PagoogEngine/vendor/glfw/src/x11_window.c",
			"PagoogEngine/vendor/glfw/src/xkb_unicode.c",
			"PagoogEngine/vendor/glfw/src/posix_time.c",
			"PagoogEngine/vendor/glfw/src/posix_thread.c",
			"PagoogEngine/vendor/glfw/src/glx_context.c",
			"PagoogEngine/vendor/glfw/src/egl_context.c",
			"PagoogEngine/vendor/glfw/src/osmesa_context.c",
			"PagoogEngine/vendor/glfw/src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"PagoogEngine/vendor/glfw/src/win32_init.c",
			"PagoogEngine/vendor/glfw/src/win32_joystick.c",
			"PagoogEngine/vendor/glfw/src/win32_monitor.c",
			"PagoogEngine/vendor/glfw/src/win32_time.c",
			"PagoogEngine/vendor/glfw/src/win32_thread.c",
			"PagoogEngine/vendor/glfw/src/win32_window.c",
			"PagoogEngine/vendor/glfw/src/wgl_context.c",
			"PagoogEngine/vendor/glfw/src/egl_context.c",
			"PagoogEngine/vendor/glfw/src/osmesa_context.c"
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



project "Glad"
    location "Glad"
	kind "StaticLib"
	language "C"

    targetdir ("Builds/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Builds/int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"PagoogEngine/vendor/glad/include/glad/glad.h",
		"PagoogEngine/vendor/glad/include/KHR/khrplatform.h",
		"PagoogEngine/vendor/glad/src/glad.c"
	}

    includedirs
    {
        "PagoogEngine/vendor/glad/include"
    }

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

    filter "configurations:Dist"
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
	    }