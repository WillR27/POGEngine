workspace "Pagoog"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "Pagoog"



outputconfigname = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
outputbindir = "%{wks.location}/Build/Builds/Bin/" .. outputconfigname
outputintdir = "%{wks.location}/Build/Builds/Int/" .. outputconfigname
outputbindirproj = outputbindir .. "/%{prj.name}"
outputintdirproj = outputintdir .. "/%{prj.name}"



function copy(source, target)
    return select(1, ("xcopy /S \"" .. source .. "\" \"" .. target .. "\""):gsub("/", "\\"))
end

copydll = copy((outputbindirproj .. "/%{prj.name}.dll"), (outputbindir .. "/Pagoog/%{prj.name}.dll"))



project "Pagoog"
    location "Internal/Pagoog"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

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
        "Internal/%{prj.name}/Source",
        "Internal/PagoogCommon/Source",
        "Internal/PagoogCore/Source",
        "Internal/PagoogDebug/Source",
        "Internal/PagoogLog/External/SPDLog/include",
        "Internal/PagoogLog/Source",
        "Internal/PagoogMaths/External/GLM",
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

        signexe = select(1, ("\"../../Build/CodeSigning/SignFiles.bat\" \"" .. outputbindirproj .. "/Pagoog.exe\""):gsub("/", "\\"))

        postbuildcommands 
        { 
            signexe,
        }



project "PagoogCommon"
    location "Internal/PagoogCommon"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

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
        "Internal/%{prj.name}/Source",
    }

    links
    {
	
	}

    defines
    {
		"PG_COMMON_EXPORT"
	}

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers"
	}

    filter "system:windows"
        systemversion "latest"
		
		postbuildcommands 
        {
            copydll,    
        }

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
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

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
        "Internal/%{prj.name}/Source",
        "Internal/PagoogCommon/Source",
        "Internal/PagoogDebug/Source",
        "Internal/PagoogLog/External/SPDLog/include",
        "Internal/PagoogLog/Source",
        "Internal/PagoogMaths/External/GLM",
        "Internal/PagoogMaths/Source",
        "Internal/PagoogRender/Source",
    }

    links
    {
        "GLFW",
		"PagoogCommon",
		"PagoogDebug",
		"PagoogLog",
		"PagoogMaths",
		"PagoogRender",
	}

    defines
    {
		"PG_CORE_EXPORT",
	}

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers"
	}

    filter "system:windows"
        systemversion "latest"
		
		postbuildcommands 
        {
            copydll,    
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
        defines { "PG_DIST" }
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
        }
        		
		
		
project "PagoogDebug"
    location "Internal/PagoogDebug"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

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
        "Internal/%{prj.name}/Source",
        "Internal/PagoogCommon/Source",
        "Internal/PagoogLog/External/SPDLog/include",
        "Internal/PagoogLog/Source",
    }

    links
    {
		"PagoogCommon",
		"PagoogLog",
	}

    defines
    {
		"PG_DEBUG_EXPORT",
	}

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers",
	}

    filter "system:windows"
        systemversion "latest"
		
		postbuildcommands 
        {
            copydll,    
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
        defines { "PG_DIST" }
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
        }
		
		
		
project "PagoogLog"
    location "Internal/PagoogLog"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

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
        "Internal/%{prj.name}/External/SPDLog/include",
		"Internal/%{prj.name}/Source",
        "Internal/PagoogCommon/Source",
    }

    links
    {
		"PagoogCommon",
	}

    defines
    {
		"PG_LOG_EXPORT",
	}

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers",
	}

    filter "system:windows"
        systemversion "latest"

        postbuildcommands 
        {
            copydll,    
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
        defines { "PG_DIST" }
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
        }



project "PagoogMaths"
    location "Internal/PagoogMaths"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

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
        "Internal/%{prj.name}/External/GLM",
		"Internal/%{prj.name}/Source",
        "Internal/PagoogCommon/Source",
    }

    links
    {
		"PagoogCommon",
	}

    defines
    {
		"PG_MATHS_EXPORT",
	}

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers",
	}

    filter "system:windows"
        systemversion "latest"
		
		postbuildcommands 
        {
            copydll,    
        }

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
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

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
        "Internal/%{prj.name}/Source",
        "Internal/PagoogCommon/Source",
        "Internal/PagoogDebug/Source",
        "Internal/PagoogLog/External/SPDLog/include",
        "Internal/PagoogLog/Source",
        "Internal/PagoogMaths/External/GLM",
        "Internal/PagoogMaths/Source",
    }

    links
    {
		"PagoogCommon",
        "PagoogDebug",
        "PagoogLog",
        "PagoogMaths",
		"Glad",
	}

    defines
    {
		"PG_RENDER_EXPORT"
	}

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers",
	}

    filter "system:windows"
        systemversion "latest"

        postbuildcommands 
        {
            copydll,    
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
        defines { "PG_DIST" }
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
	    }



project "PagoogTest"
    location "Internal/PagoogTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "Off"

    targetdir (outputbindir .. "/Pagoog")
    objdir (outputintdirproj)

    files
    {
        "Internal/%{prj.name}/Source/**.h",
        "Internal/%{prj.name}/Source/**.cpp",
        "Internal/%{prj.name}/Source/**.hpp",
    }

    includedirs
    {
        "External/GoogleTest/googletest/include",
        "External/GoogleTest/googlemock/include",
        "Internal/%{prj.name}/Source",
        "Internal/PagoogCommon/Source",
        "Internal/PagoogCore/Source",
        "Internal/PagoogDebug/Source",
        "Internal/PagoogLog/External/SPDLog/include",
        "Internal/PagoogLog/Source",
        "Internal/PagoogMaths/External/GLM",
        "Internal/PagoogMaths/Source",
        "Internal/PagoogRender/Source",
    }

    links
    {
        "GoogleTest",
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



project "GoogleTest"
    location "External/GoogleTest"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    files
    {
        "External/%{prj.name}/googlemock/src/gmock-all.cc",
        "External/%{prj.name}/googletest/src/gtest-all.cc",
    }

    includedirs
    {
        "External/%{prj.name}/googletest",
        "External/%{prj.name}/googlemock",
        "External/%{prj.name}/googletest/include",
        "External/%{prj.name}/googlemock/include",
    }

    links
    {

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



project "Glad"
    location "External/Glad"
	kind "StaticLib"
	language "C"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

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
		staticruntime "Off"

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