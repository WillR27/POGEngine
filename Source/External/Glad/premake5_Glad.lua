project "Glad"
    location "External/Glad"
	kind "StaticLib"
	language "C"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

	files
	{
		"External/%{prj.name}/include/glad/glad.h",
		"External/%{prj.name}/include/KHR/khrplatform.h",
		"External/%{prj.name}/src/glad.c",
	}

    includedirs
    {
        "External/%{prj.name}/include",
    }

    flags
    {
        "MultiProcessorCompile",
        "UndefinedIdentifiers",
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "Off"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

    filter "configurations:Dist"
        runtime "Release"
        optimize "On"

        flags
        {
            "LinkTimeOptimization"
	    }