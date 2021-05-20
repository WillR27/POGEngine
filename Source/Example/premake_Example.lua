createbaseprojectcpp("Example", "SharedLib")
    pchheader "ExamplePCH.h"
	pchsource "Source/ExamplePCH.cpp"
	
    includedirs
    {
		"../../External/Glad/include",
	
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
		"Glad",
	
		"POGCommon",
		"POGCore",
		"POGDebug",
		"POGLog",
		"POGMaths",
		"POGRender",
    }
	
	defines
	{
		--"POG_STANDALONE",
	}

    filter "configurations:Dist"
        signexe = select(1, ("\"%{wks.location}/CodeSigning/SignFiles.bat\" \"" .. outputbindirproj .. "/Example.exe\""):gsub("/", "\\"))

        postbuildcommands 
        { 
            --signexe,
        }