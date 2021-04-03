project "Glad"
	kind "StaticLib"
	language "C"

    targetdir (outputbindirproj)
    objdir (outputintdirproj)

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c",
	}

    includedirs
    {
        "include",
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