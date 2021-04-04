createbaseprojectcpp("POGCommon", "SharedLib")
    pchheader "POGCommonPCH.h"
	pchsource "Source/POGCommonPCH.cpp"
    
    defines
    {
		"POG_COMMON_EXPORT"
	}