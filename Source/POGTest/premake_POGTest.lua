createbaseprojectcpp("POGTest", "ConsoleApp")
	includedirs
    {
        "GoogleTest/googletest/include",
        "GoogleTest/googlemock/include",
		
        "../POGCommon/Source",
        "../POGCore/Source",
        "../POGDebug/Source",
        "../POGLog/SPDLog/include",
        "../POGLog/Source",
        "../POGMaths/GLM",
        "../POGMaths/Source",
        "../POGRender/Source",
    }

    links
    {
        "GoogleTest",
		
		"POGCommon",
		"POGCore",
		"POGDebug",
		"POGLog",
		"POGMaths",
		"POGRender",
    }