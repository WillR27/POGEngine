project "POGLog"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    pchheader "POGLogPCH.h"
	pchsource "Source/POGLogPCH.cpp"

    files
    {
        "Source/**.h",
        "Source/**.cpp",
        "Source/**.hpp",
    }

    includedirs
    {
        "SPDLog/include",
		
		"Source",
        "../POGCommon/Source",
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