createbaseprojectcpp("POGTest", "ConsoleApp")
	includedirs
    {
        "../../External/GoogleTest/googletest/include",
        "../../External/GoogleTest/googlemock/include",
		
        "../POGCommon/Source",
        "../POGCore/Source",
        "../POGDebug/Source",
        "../POGGraphics/Source",
        "../POGLog/SPDLog/include",
        "../POGLog/Source",
        "../POGMaths/GLM",
        "../POGMaths/Source",
    }

    links
    {
        "GoogleTest",
		
		"POGCommon",
		"POGCore",
		"POGDebug",
		"POGGraphics",
		"POGLog",
		"POGMaths",
    }