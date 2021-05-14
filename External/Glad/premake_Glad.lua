createbaseprojectcpp("Glad", "StaticLib")
	language "C"

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