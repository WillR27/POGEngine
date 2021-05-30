createbaseprojectcpp("POGUtil", "StaticLib")
    pchheader "POGUtilPCH.h"
	pchsource "Source/POGUtilPCH.cpp"
	
	includedirs
    {
        "../POGCommon/Source",
    }

    links
    {
		"POGCommon"
	}