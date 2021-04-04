createbaseprojectcpp("Example", "ConsoleApp")
    pchheader "ExamplePCH.h"
	pchsource "Source/ExamplePCH.cpp"
	
    includedirs
    {
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
		"POGCommon",
		"POGCore",
		"POGDebug",
		"POGLog",
		"POGMaths",
		"POGRender",
    }

    filter "configurations:Dist"
        signexe = select(1, ("\"%{wks.location}/CodeSigning/SignFiles.bat\" \"" .. outputbindirproj .. "/Example.exe\""):gsub("/", "\\"))

        postbuildcommands 
        { 
            signexe,
        }