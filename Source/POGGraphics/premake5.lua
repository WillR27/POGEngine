createbaseprojectcpp("POGGraphics", "StaticLib")
    pchheader "POGGraphicsPCH.h"
	pchsource "Source/POGGraphicsPCH.cpp"

    includedirs
    {
        "../../External/FreeType/include",
        "../../External/Glad/include",
		
        "../POGCommon/Source",
        "../POGDebug/Source",
        "../POGLog/SPDLog/include",
        "../POGLog/Source",
        "../POGMaths/GLM",
        "../POGMaths/Source",
        "../POGUtil/Stb",
        "../POGUtil/Source",
    }

    links
    {
		"FreeType",
		"Glad",
	
		"POGCommon",
        "POGDebug",
        "POGLog",
        "POGMaths",
	}