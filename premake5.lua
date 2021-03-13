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

    pchheader "PagoogPCH.h"
	pchsource "%{prj.name}/Source/PagoogPCH.cpp"
	
    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
        "%{prj.name}/Source/**.hpp"
    }

    includedirs
    {
        "PagoogLog/External/spdlog/include",
        "%{prj.name}/Source",
		"",
    }

    links
    {
		"PagoogCommon",
		"PagoogCore",
		"PagoogLog",
		"PagoogDebug",
		"PagoogRender"
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
        defines { "PG_DEBUG", "PG_ENABLE_ASSERT" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "PG_RELEASE", "PG_ENABLE_VERIFY" }
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


		
project "PagoogCommon"
    location "PagoogCommon"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "On"

    targetdir ("Builds/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Builds/int/" .. outputdir .. "/%{prj.name}")

    pchheader "PagoogCommonPCH.h"
	pchsource "%{prj.name}/Source/PagoogCommonPCH.cpp"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
        "%{prj.name}/Source/**.hpp"
    }

    includedirs
    {
        "PagoogLog/External/spdlog/include",
        "%{prj.name}/Source",
    }

    links
    {
	
	}

    defines
    {

	}

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers"
	}

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "PG_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "PG_RELEASE" }
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
		
		

project "PagoogCore"
    location "PagoogCore"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "On"

    targetdir ("Builds/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Builds/int/" .. outputdir .. "/%{prj.name}")

    pchheader "PagoogCorePCH.h"
	pchsource "%{prj.name}/Source/PagoogCorePCH.cpp"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
        "%{prj.name}/Source/**.hpp"
    }

    includedirs
    {
        "PagoogLog/External/spdlog/include",
        "%{prj.name}/Source",
		"",
    }

    links
    {
		"PagoogCommon",
		"PagoogLog",
		"PagoogDebug"
	}

    defines
    {

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
        		
		
		
project "PagoogDebug"
    location "PagoogDebug"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "On"

    targetdir ("Builds/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Builds/int/" .. outputdir .. "/%{prj.name}")

    pchheader "PagoogDebugPCH.h"
	pchsource "%{prj.name}/Source/PagoogDebugPCH.cpp"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
        "%{prj.name}/Source/**.hpp",
    }

    includedirs
    {
        "PagoogLog/External/spdlog/include",
        "%{prj.name}/Source",
		"",
    }

    links
    {
		"PagoogCommon",
		"PagoogLog",
	}

    defines
    {

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
		
		
		
project "PagoogLog"
    location "PagoogLog"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "On"

    targetdir ("Builds/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Builds/int/" .. outputdir .. "/%{prj.name}")

    pchheader "PagoogLogPCH.h"
	pchsource "%{prj.name}/Source/PagoogLogPCH.cpp"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
        "%{prj.name}/Source/**.hpp",
    }

    includedirs
    {
        "%{prj.name}/External/spdlog/include",
		"%{prj.name}/Source",
		"",
    }

    links
    {
		"PagoogCommon",
	}

    defines
    {

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
		

		
project "PagoogRender"
    location "PagoogRender"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "On"

    targetdir ("Builds/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Builds/int/" .. outputdir .. "/%{prj.name}")

    pchheader "PagoogRenderPCH.h"
	pchsource "%{prj.name}/Source/PagoogRenderPCH.cpp"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
        "%{prj.name}/Source/**.hpp"
    }

    includedirs
    {
        "PagoogLog/External/spdlog/include",
        "%{prj.name}/Source",
		"",
    }

    links
    {
		"PagoogCommon",
		"Glad",
		"GLFW",
	}

    defines
    {
		
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
		"%{prj.name}/include/GLFW/glfw3.h",
		"%{prj.name}/include/GLFW/glfw3native.h",
		"%{prj.name}/src/glfw_config.h",
		"%{prj.name}/src/context.c",
		"%{prj.name}/src/init.c",
		"%{prj.name}/src/input.c",
		"%{prj.name}/src/monitor.c",
		"%{prj.name}/src/vulkan.c",
		"%{prj.name}/src/window.c"
	}

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"%{prj.name}/src/win32_init.c",
			"%{prj.name}/src/win32_joystick.c",
			"%{prj.name}/src/win32_monitor.c",
			"%{prj.name}/src/win32_time.c",
			"%{prj.name}/src/win32_thread.c",
			"%{prj.name}/src/win32_window.c",
			"%{prj.name}/src/wgl_context.c",
			"%{prj.name}/src/egl_context.c",
			"%{prj.name}/src/osmesa_context.c"
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
		"%{prj.name}/include/glad/glad.h",
		"%{prj.name}/include/KHR/khrplatform.h",
		"%{prj.name}/src/glad.c"
	}

    includedirs
    {
        "%{prj.name}/include"
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