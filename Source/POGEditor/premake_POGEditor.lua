createbaseprojectcpp("POGEditor", "ConsoleApp")
    pchheader "POGEditorPCH.h"
	pchsource "Source/POGEditorPCH.cpp"
	
	includedirs
    {
		"../../External/Glad/include",
		"../../External/ImGui",
	
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
		"ImGui",
		
		"POGCommon",
		"POGCore",
		"POGDebug",
		"POGLog",
		"POGMaths",
		"POGRender",
    }
	
	defines
	{
		"POG_STANDALONE",
	}