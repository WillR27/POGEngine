createbaseprojectcpp("Example", "ConsoleApp")
    pchheader "ExamplePCH.h"
	pchsource "Source/ExamplePCH.cpp"
	
    targetdir (outputbindirproj)
    objdir (outputintdirproj)

    includedirs
    {
		"../../External/Glad/include",
	
        "../POGCommon/Source",
        "../POGCore/Source",
        "../POGDebug/Source",
        "../POGGraphics/Source",
        "../POGLog/SPDLog/include",
        "../POGLog/Source",
        "../POGMaths/GLM",
        "../POGMaths/Source",
		"../POGUtil/Source",
    }

    links
    {
		"Glad",
	
		"POGCommon",
		"POGCore",
		"POGDebug",
		"POGGraphics",
		"POGLog",
		"POGMaths",
		"POGUtil",
    }
	
	defines
	{
		"POG_STANDALONE",
	}

    postbuildcommands 
    { 
        copyfolder("%{prj.location}/Resources", outputbindirproj .. "/Resources/")
    }

    filter "configurations:Dist"
        signexe = select(1, ("\"%{wks.location}/CodeSigning/SignFiles.bat\" \"" .. outputbindirproj .. "/Example.exe\""):gsub("/", "\\"))

        postbuildcommands 
        { 
            --signexe,
        }