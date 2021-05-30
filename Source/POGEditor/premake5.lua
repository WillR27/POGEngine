createbaseprojectcpp("POGEditor", "ConsoleApp")
    pchheader "POGEditorPCH.h"
	pchsource "Source/POGEditorPCH.cpp"
	
	includedirs
    {
		"../../External/Glad/include",
		"../../External/GLFW/include",
		"../../External/ImGui",
	
        "../POGCommon/Source",
        "../POGCore/Source",
        "../POGDebug/Source",
        "../POGLog/SPDLog/include",
        "../POGLog/Source",
        "../POGMaths/GLM",
        "../POGMaths/Source",
        "../POGRender/Source",
		"../POGUtil/Source",
    }

    links
    {
		"Glad",
		"GLFW",
		"ImGui",
		
		"POGCommon",
		"POGCore",
		"POGDebug",
		"POGLog",
		"POGMaths",
		"POGRender",
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