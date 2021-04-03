project "POGCore"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    pchheader "POGCorePCH.h"
	pchsource "Source/POGCorePCH.cpp"

    files
    {
        "Source/**.h",
        "Source/**.cpp",
        "Source/**.hpp"
    }

    includedirs
    {
        "GLFW/include",
		
        "Source",
        "../POGCommon/Source",
        "../POGDebug/Source",
        "../POGLog/External/SPDLog/include",
        "../POGLog/Source",
        "../POGMaths/External/GLM",
        "../POGMaths/Source",
        "../POGRender/Source",
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