project "POGTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "Off"

    targetdir (outputbindir .. "/Example")
    objdir (outputintdirproj)

    files
    {
        "Source/**.h",
        "Source/**.cpp",
        "Source/**.hpp",
    }

    includedirs
    {
        "GoogleTest/googletest/include",
        "GoogleTest/googlemock/include",
		
        "Source",
        "../POGCommon/Source",
        "../POGCore/Source",
        "../POGDebug/Source",
        "../POGLog/External/SPDLog/include",
        "../POGLog/Source",
        "../POGMaths/External/GLM",
        "../POGMaths/Source",
        "../POGRender/Source",
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