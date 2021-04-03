project "Example"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "Off"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    pchheader "ExamplePCH.h"
	pchsource "Source/ExamplePCH.cpp"
	
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

        signexe = select(1, ("\"../../Build/CodeSigning/SignFiles.bat\" \"" .. outputbindirproj .. "/POG.exe\""):gsub("/", "\\"))

        postbuildcommands 
        { 
            signexe,
        }