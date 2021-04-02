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