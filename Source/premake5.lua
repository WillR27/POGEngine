workspace "POGEngine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "Example"



outputconfigname = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
outputbindir = "%{wks.location}/Build/Builds/Bin/" .. outputconfigname
outputintdir = "%{wks.location}/Build/Builds/Int/" .. outputconfigname
outputbindirproj = outputbindir .. "/%{prj.name}"
outputintdirproj = outputintdir .. "/%{prj.name}"



function copy(source, target)
    return "xcopy /y \"" .. select(1, (source .. "\" \"" .. target .. "\""):gsub("/", "\\"))
end

copydll = copy((outputbindirproj .. "/%{prj.name}.dll"), (outputbindir .. "/Example/"))



project "Example"
    location "Internal/Example"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    pchheader "ExamplePCH.h"
	pchsource "Internal/%{prj.name}/Source/ExamplePCH.cpp"
	
    files
    {
        "Internal/%{prj.name}/Source/**.h",
        "Internal/%{prj.name}/Source/**.cpp",
        "Internal/%{prj.name}/Source/**.hpp",
    }

    includedirs
    {
        "Internal/%{prj.name}/Source",
        "Internal/POGCommon/Source",
        "Internal/POGCore/Source",
        "Internal/POGDebug/Source",
        "Internal/POGLog/External/SPDLog/include",
        "Internal/POGLog/Source",
        "Internal/POGMaths/External/GLM",
        "Internal/POGMaths/Source",
        "Internal/POGRender/Source",
    }

    links
    {
		"POGCommon",
		"POGCore",
		"POGDebug",
		"POGLog",
		"POGMaths",
		"POGRender",
    }

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers",
	}

    filter "configurations:Debug"
        defines { "POG_DEBUG", "POG_ENABLE_ASSERT" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "POG_RELEASE", "POG_ENABLE_VERIFY" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "POG_DIST"
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
	    }

        signexe = select(1, ("\"../../Build/CodeSigning/SignFiles.bat\" \"" .. outputbindirproj .. "/POG.exe\""):gsub("/", "\\"))

        postbuildcommands 
        { 
            signexe,
        }



project "POGCommon"
    location "Internal/POGCommon"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    pchheader "POGCommonPCH.h"
	pchsource "Internal/%{prj.name}/Source/POGCommonPCH.cpp"

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
		"POG_COMMON_EXPORT"
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
        defines { "POG_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "POG_RELEASE" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "POG_DIST" }
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
        }
		
		

project "POGCore"
    location "Internal/POGCore"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    pchheader "POGCorePCH.h"
	pchsource "Internal/%{prj.name}/Source/POGCorePCH.cpp"

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
        "Internal/POGCommon/Source",
        "Internal/POGDebug/Source",
        "Internal/POGLog/External/SPDLog/include",
        "Internal/POGLog/Source",
        "Internal/POGMaths/External/GLM",
        "Internal/POGMaths/Source",
        "Internal/POGRender/Source",
    }

    links
    {
        "GLFW",
		"POGCommon",
		"POGDebug",
		"POGLog",
		"POGMaths",
		"POGRender",
	}

    defines
    {
		"POG_CORE_EXPORT",
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
        defines { "POG_DEBUG", "POG_ENABLE_ASSERT" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "POG_RELEASE", "POG_ENABLE_VERIFY" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "POG_DIST" }
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
        }
        		
		
		
project "POGDebug"
    location "Internal/POGDebug"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    pchheader "POGDebugPCH.h"
	pchsource "Internal/%{prj.name}/Source/POGDebugPCH.cpp"

    files
    {
        "Internal/%{prj.name}/Source/**.h",
        "Internal/%{prj.name}/Source/**.cpp",
        "Internal/%{prj.name}/Source/**.hpp",
    }

    includedirs
    {
        "Internal/%{prj.name}/Source",
        "Internal/POGCommon/Source",
        "Internal/POGLog/External/SPDLog/include",
        "Internal/POGLog/Source",
    }

    links
    {
		"POGCommon",
		"POGLog",
	}

    defines
    {
		"POG_DEBUG_EXPORT",
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
        defines { "POG_DEBUG", "POG_ENABLE_ASSERT" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "POG_RELEASE", "POG_ENABLE_VERIFY" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "POG_DIST" }
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
        }
		
		
		
project "POGLog"
    location "Internal/POGLog"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    pchheader "POGLogPCH.h"
	pchsource "Internal/%{prj.name}/Source/POGLogPCH.cpp"

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
        "Internal/POGCommon/Source",
    }

    links
    {
		"POGCommon",
	}

    defines
    {
		"POG_LOG_EXPORT",
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
        defines { "POG_DEBUG", "POG_ENABLE_ASSERT" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "POG_RELEASE", "POG_ENABLE_VERIFY" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "POG_DIST" }
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
        }



project "POGMaths"
    location "Internal/POGMaths"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    pchheader "POGMathsPCH.h"
	pchsource "Internal/%{prj.name}/Source/POGMathsPCH.cpp"

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
        "Internal/POGCommon/Source",
    }

    links
    {
		"POGCommon",
	}

    defines
    {
		"POG_MATHS_EXPORT",
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
        defines { "POG_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "POG_RELEASE" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "POG_DIST" }
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
        }
		

		
project "POGRender"
    location "Internal/POGRender"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    pchheader "POGRenderPCH.h"
	pchsource "Internal/%{prj.name}/Source/POGRenderPCH.cpp"

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
        "Internal/POGCommon/Source",
        "Internal/POGDebug/Source",
        "Internal/POGLog/External/SPDLog/include",
        "Internal/POGLog/Source",
        "Internal/POGMaths/External/GLM",
        "Internal/POGMaths/Source",
    }

    links
    {
		"POGCommon",
        "POGDebug",
        "POGLog",
        "POGMaths",
		"Glad",
	}

    defines
    {
		"POG_RENDER_EXPORT"
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
        defines { "POG_DEBUG", "POG_ENABLE_ASSERT" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "POG_RELEASE", "POG_ENABLE_VERIFY" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "POG_DIST" }
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
	    }



project "POGTest"
    location "Internal/POGTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "Off"

    targetdir (outputbindir .. "/Example")
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
        "Internal/POGCommon/Source",
        "Internal/POGCore/Source",
        "Internal/POGDebug/Source",
        "Internal/POGLog/External/SPDLog/include",
        "Internal/POGLog/Source",
        "Internal/POGMaths/External/GLM",
        "Internal/POGMaths/Source",
        "Internal/POGRender/Source",
    }

    links
    {
        "GoogleTest",
		"POGCommon",
		"POGCore",
		"POGDebug",
		"POGLog",
		"POGMaths",
		"POGRender",
    }

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers",
	}
	
    filter "configurations:Debug"
        defines { "POG_DEBUG", "POG_ENABLE_ASSERT" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "POG_RELEASE", "POG_ENABLE_VERIFY" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "POG_DIST"
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
        defines { "POG_DEBUG", "POG_ENABLE_ASSERT" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "POG_RELEASE", "POG_ENABLE_VERIFY" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "POG_DIST"
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