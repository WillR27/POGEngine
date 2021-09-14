include "premake_POGEngineBase.lua"


workspace "POGEngine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "Example"
	
	solutionitems 
	{
		{ ["Workspace Items"] = 
			{ 
				".gitignore",
				"premake5.lua",
				"premake_Base.lua",
				"premake_POGEngineBase.lua",
			} 
		},
	}

	
group "External Dependencies"
	include "External/FreeType/premake5.lua"
	include "External/GLFW/premake5.lua"
	include "External/Glad/premake5.lua"
	include "External/GoogleTest/premake5.lua"
	include "External/ImGui/premake5.lua"

group "Examples"
	include "Source/Example/premake5.lua"
	
group "POG Editor"
	include "Source/POGEditor/premake5.lua"
	
group "POG Engine"
	include "Source/POGCommon/premake5.lua"
	include "Source/POGCore/premake5.lua"
	include "Source/POGDebug/premake5.lua"
	include "Source/POGGraphics/premake5.lua"
	include "Source/POGLog/premake5.lua"
	include "Source/POGMaths/premake5.lua"
	include "Source/POGTest/premake5.lua"
	include "Source/POGUtil/premake5.lua"








