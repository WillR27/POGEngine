createbaseprojectcpp("POGCore", "SharedLib")
    pchheader "POGCorePCH.h"
	pchsource "Source/POGCorePCH.cpp"

    includedirs
    {
        "GLFW/include",
		
        "../POGCommon/Source",
        "../POGDebug/Source",
        "../POGLog/SPDLog/include",
        "../POGLog/Source",
        "../POGMaths/GLM",
        "../POGMaths/Source",
        "../POGRender/Source",
    }

    links
    {
        "GLFW",
		
		"POGCommon",
		"POGDebug",
		"POGLog",
		"POGMaths",
		"POGRender",
	}

    defines
    {
		"POG_CORE_EXPORT",
	}