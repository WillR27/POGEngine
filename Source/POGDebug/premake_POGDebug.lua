createbaseprojectcpp("POGDebug", "SharedLib")
    pchheader "POGDebugPCH.h"
	pchsource "Source/POGDebugPCH.cpp"

    includedirs
    {
        "../POGCommon/Source",
        "../POGLog/External/SPDLog/include",
        "../POGLog/Source",
    }

    links
    {
		"POGCommon",
		"POGLog",
	}

    defines
    {
		"POG_DEBUG_EXPORT",
	}