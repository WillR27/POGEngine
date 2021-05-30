createbaseprojectcpp("POGUtil", "StaticLib")
    pchheader "POGUtilPCH.h"
	pchsource "Source/POGUtilPCH.cpp"
	
	includedirs
    {
        "Stb",

        "../POGCommon/Source",
    }

    links
    {
		"POGCommon",
	}

    defines
    {
        "STB_IMAGE_IMPLEMENTATION",
    }