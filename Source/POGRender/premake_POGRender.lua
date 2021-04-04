createbaseprojectcpp("POGRender", "SharedLib")
    pchheader "POGRenderPCH.h"
	pchsource "Source/POGRenderPCH.cpp"

    includedirs
    {
        "Glad/include",
		
        "../POGCommon/Source",
        "../POGDebug/Source",
        "../POGLog/SPDLog/include",
        "../POGLog/Source",
        "../POGMaths/GLM",
        "../POGMaths/Source",
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