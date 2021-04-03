project "POGMaths"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    pchheader "POGMathsPCH.h"
	pchsource "Source/POGMathsPCH.cpp"

    files
    {
        "Source/**.h",
        "Source/**.cpp",
        "Source/**.hpp",
    }

    includedirs
    {
        "GLM",
		
		"Source",
        "../POGCommon/Source",
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