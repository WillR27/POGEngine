createbaseprojectcpp("POGEditor", "ConsoleApp")
    pchheader "POGEditorPCH.h"
	pchsource "Source/POGEditorPCH.cpp"
	
	files
	{
		"ImGui/**.h",
		"ImGui/**.cpp",
		"ImGui/**.hpp",
	}
	
	includedirs
    {
		"ImGui",
	
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