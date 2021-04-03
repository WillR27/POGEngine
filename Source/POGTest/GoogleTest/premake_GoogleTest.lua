project "GoogleTest"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    files
    {
        "googlemock/src/gmock-all.cc",
        "googletest/src/gtest-all.cc",
    }

    includedirs
    {
        "googletest",
        "googlemock",
        "googletest/include",
        "googlemock/include",
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