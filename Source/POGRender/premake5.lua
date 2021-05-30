createbaseprojectcpp("POGRender", "StaticLib")
    pchheader "POGRenderPCH.h"
	pchsource "Source/POGRenderPCH.cpp"

    includedirs
    {
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
		"Glad",
	
		"POGCommon",
        "POGDebug",
        "POGLog",
        "POGMaths",
	}

    defines
    {
		"POG_RENDER_EXPORT"
	}