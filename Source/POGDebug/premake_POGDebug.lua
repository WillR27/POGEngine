project "POGDebug"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    pchheader "POGDebugPCH.h"
	pchsource "Source/POGDebugPCH.cpp"

    files
    {
        "Source/**.h",
        "Source/**.cpp",
        "Source/**.hpp",
    }

    includedirs
    {
        "Source",
        "../POGCommon/Source",
        "../POGLog/External/SPDLog/include",
        "../POGLog/Source",
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