createbaseprojectcpp("GoogleTest", "StaticLib")
    files
    {
        "googlemock/src/gmock-all.cc",
        "googletest/src/gtest-all.cc",
    }

    includedirs
    {
        "googletest",
        "googlemock",
        "googletest/include",
        "googlemock/include",
    }