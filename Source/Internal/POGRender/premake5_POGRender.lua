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