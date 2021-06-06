createbaseprojectcpp("POGCore", "StaticLib")
    pchheader "POGCorePCH.h"
	pchsource "Source/POGCorePCH.cpp"

    includedirs
    {
        "../../External/GLFW/include",
		
        "../POGCommon/Source",
        "../POGDebug/Source",
        "../POGGraphics/Source",
        "../POGLog/SPDLog/include",
        "../POGLog/Source",
        "../POGMaths/GLM",
        "../POGMaths/Source",
		"../POGUtil/Source",
    }

    links
    {
        "GLFW",
		
		"POGCommon",
		"POGDebug",
		"POGGraphics",
		"POGLog",
		"POGMaths",
		"POGUtil"
	}

    defines
    {
		"POG_CORE_EXPORT",
	}