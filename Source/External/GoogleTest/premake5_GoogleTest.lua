project "GoogleTest"
    location "External/GoogleTest"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    files
    {
        "External/%{prj.name}/googlemock/src/gmock-all.cc",
        "External/%{prj.name}/googletest/src/gtest-all.cc",
    }

    includedirs
    {
        "External/%{prj.name}/googletest",
        "External/%{prj.name}/googlemock",
        "External/%{prj.name}/googletest/include",
        "External/%{prj.name}/googlemock/include",
    }

    links
    {

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