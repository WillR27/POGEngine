project "POGRender"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    pchheader "POGRenderPCH.h"
	pchsource "Source/POGRenderPCH.cpp"

    files
    {
        "Source/**.h",
        "Source/**.cpp",
        "Source/**.hpp",
    }

    includedirs
    {
        "Glad/include",
		
        "Source",
        "../POGCommon/Source",
        "../POGDebug/Source",
        "../POGLog/External/SPDLog/include",
        "../POGLog/Source",
        "../POGMaths/External/GLM",
        "../POGMaths/Source",
    }

    links
    {
		"Glad",
	
		"POGCommon",
        "POGDebug",
        "POGLog",
        "POGMaths",
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