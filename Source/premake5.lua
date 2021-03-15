workspace "Pagoog"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "Pagoog"



outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
outputbindir = "Build/Builds/Bin/" .. outputdir .. "/%{prj.name}"
outputintdir = "Build/Builds/Int/" .. outputdir .. "/%{prj.name}"



project "Pagoog"
    location "Internal/Pagoog"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "On"

    targetdir (outputbindir)
    objdir (outputintdir)

    pchheader "PagoogPCH.h"
	pchsource "Internal/%{prj.name}/Source/PagoogPCH.cpp"
	
    files
    {
        "Internal/%{prj.name}/Source/**.h",
        "Internal/%{prj.name}/Source/**.cpp",
        "Internal/%{prj.name}/Source/**.hpp",
    }

    includedirs
    {
        "External/Glad/include",
        "External/GLM/include",
        "External/SPDLog/include",
        "Internal/%{prj.name}/Source",
        "Internal/PagoogCommon/Source",
        "Internal/PagoogCore/Source",
        "Internal/PagoogDebug/Source",
        "Internal/PagoogLog/Source",
        "Internal/PagoogMaths/Source",
        "Internal/PagoogRender/Source",
    }

    links
    {
		"PagoogCommon",
		"PagoogCore",
		"PagoogDebug",
		"PagoogLog",
		"PagoogMaths",
		"PagoogRender",
    }

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers",
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

        signexe = select(1, ("\"../../Build/CodeSigning/SignFiles.bat\" \"" .. "%{wks.location}" .. outputbindir .. "/Pagoog.exe\""):gsub("/", "\\"))

        postbuildcommands 
        { 
            signexe,
        }



project "PagoogCommon"
    location "Internal/PagoogCommon"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "On"

    targetdir (outputbindir)
    objdir (outputintdir)

    pchheader "PagoogCommonPCH.h"
	pchsource "Internal/%{prj.name}/Source/PagoogCommonPCH.cpp"

    files
    {
        "Internal/%{prj.name}/Source/**.h",
        "Internal/%{prj.name}/Source/**.cpp",
        "Internal/%{prj.name}/Source/**.hpp"
    }

    includedirs
    {
        "External/SPDLog/include",
        "Internal/%{prj.name}/Source",
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
    location "Internal/PagoogCore"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "On"

    targetdir (outputbindir)
    objdir (outputintdir)

    pchheader "PagoogCorePCH.h"
	pchsource "Internal/%{prj.name}/Source/PagoogCorePCH.cpp"

    files
    {
        "Internal/%{prj.name}/Source/**.h",
        "Internal/%{prj.name}/Source/**.cpp",
        "Internal/%{prj.name}/Source/**.hpp"
    }

    includedirs
    {
        "External/GLFW/include",
        "External/GLM/include",
        "External/SPDLog/include",
        "Internal/%{prj.name}/Source",
        "Internal/PagoogCommon/Source",
        "Internal/PagoogDebug/Source",
        "Internal/PagoogLog/Source",
    }

    links
    {
		"PagoogCommon",
		"PagoogDebug",
		"PagoogLog",
		"PagoogMaths",
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
    location "Internal/PagoogDebug"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "On"

    targetdir (outputbindir)
    objdir (outputintdir)

    pchheader "PagoogDebugPCH.h"
	pchsource "Internal/%{prj.name}/Source/PagoogDebugPCH.cpp"

    files
    {
        "Internal/%{prj.name}/Source/**.h",
        "Internal/%{prj.name}/Source/**.cpp",
        "Internal/%{prj.name}/Source/**.hpp",
    }

    includedirs
    {
        "External/SPDLog/include",
        "Internal/%{prj.name}/Source",
        "Internal/PagoogCommon/Source",
        "Internal/PagoogLog/Source",
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
        "UndefinedIdentifiers",
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
    location "Internal/PagoogLog"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "On"

    targetdir (outputbindir)
    objdir (outputintdir)

    pchheader "PagoogLogPCH.h"
	pchsource "Internal/%{prj.name}/Source/PagoogLogPCH.cpp"

    files
    {
        "Internal/%{prj.name}/Source/**.h",
        "Internal/%{prj.name}/Source/**.cpp",
        "Internal/%{prj.name}/Source/**.hpp",
    }

    includedirs
    {
        "External/SPDLog/include",
		"Internal/%{prj.name}/Source",
        "Internal/PagoogCommon/Source",
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
        "UndefinedIdentifiers",
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



project "PagoogMaths"
    location "Internal/PagoogMaths"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "On"

    targetdir (outputbindir)
    objdir (outputintdir)

    pchheader "PagoogMathsPCH.h"
	pchsource "Internal/%{prj.name}/Source/PagoogMathsPCH.cpp"

    files
    {
        "Internal/%{prj.name}/Source/**.h",
        "Internal/%{prj.name}/Source/**.cpp",
        "Internal/%{prj.name}/Source/**.hpp",
    }

    includedirs
    {
        "External/GLM/include",
		"Internal/%{prj.name}/Source",
        "Internal/PagoogCommon/Source",
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
        "UndefinedIdentifiers",
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
		

		
project "PagoogRender"
    location "Internal/PagoogRender"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "On"

    targetdir (outputbindir)
    objdir (outputintdir)

    pchheader "PagoogRenderPCH.h"
	pchsource "Internal/%{prj.name}/Source/PagoogRenderPCH.cpp"

    files
    {
        "Internal/%{prj.name}/Source/**.h",
        "Internal/%{prj.name}/Source/**.cpp",
        "Internal/%{prj.name}/Source/**.hpp",
    }

    includedirs
    {
        "External/Glad/include",
        "External/GLM/include",
        "External/SPDLog/include",
        "Internal/%{prj.name}/Source",
        "Internal/PagoogCommon/Source",
        "Internal/PagoogDebug/Source",
        "Internal/PagoogLog/Source",
    }

    links
    {
		"PagoogCommon",
        "PagoogDebug",
        "PagoogLog",
        "PagoogMaths",
		"Glad",
		"GLFW",
	}

    defines
    {
		
	}

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers",
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
    location "External/GLFW"
	kind "StaticLib"
	language "C"

    targetdir (outputbindir)
    objdir (outputintdir)

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
		staticruntime "On"

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



project "Glad"
    location "External/Glad"
	kind "StaticLib"
	language "C"

    targetdir (outputbindir)
    objdir (outputintdir)

	files
	{
		"External/%{prj.name}/include/glad/glad.h",
		"External/%{prj.name}/include/KHR/khrplatform.h",
		"External/%{prj.name}/src/glad.c",
	}

    includedirs
    {
        "External/%{prj.name}/include",
    }

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers",
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