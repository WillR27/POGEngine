createbaseprojectcpp("POGMaths", "SharedLib")
    pchheader "POGMathsPCH.h"
	pchsource "Source/POGMathsPCH.cpp"

    includedirs
    {
        "GLM",
		
        "../POGCommon/Source",
    }

    links
    {
		"POGCommon",
	}

    defines
    {
		"POG_MATHS_EXPORT",
	}