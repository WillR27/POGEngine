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