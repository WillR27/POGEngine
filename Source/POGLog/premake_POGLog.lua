createbaseprojectcpp("POGLog", "SharedLib")
    pchheader "POGLogPCH.h"
	pchsource "Source/POGLogPCH.cpp"

    includedirs
    {
        "SPDLog/include",
		
        "../POGCommon/Source",
    }

    links
    {
		"POGCommon",
	}

    defines
    {
		"POG_LOG_EXPORT",
	}