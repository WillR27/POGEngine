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