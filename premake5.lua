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
	include "External/GLFW/premake_GLFW.lua"
	include "External/Glad/premake_Glad.lua"
	include "External/GoogleTest/premake_GoogleTest.lua"
	include "External/ImGui/premake_ImGui.lua"

group "Examples"
	include "Source/Example/premake_Example.lua"
	
group "POG Editor"
	include "Source/POGEditor/premake_POGEditor.lua"
	
group "POG Engine"
	include "Source/POGCommon/premake_POGCommon.lua"
	include "Source/POGCore/premake_POGCore.lua"
	include "Source/POGDebug/premake_POGDebug.lua"
	include "Source/POGLog/premake_POGLog.lua"
	include "Source/POGMaths/premake_POGMaths.lua"
	include "Source/POGRender/premake_POGRender.lua"
	include "Source/POGTest/premake_POGTest.lua"








