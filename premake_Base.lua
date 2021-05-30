function copyfile(source, target)
    return "xcopy /y \"" .. select(1, (source .. "\" \"" .. target .. "\""):gsub("/", "\\"))
end

function copyfolder(source, target)
    return "xcopy /y /s \"" .. select(1, (source .. "\" \"" .. target .. "\""):gsub("/", "\\"))
end


outputconfigname = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
outputbindir = "%{wks.location}/Out/Bin/" .. outputconfigname
outputintdir = "%{wks.location}/Out/Int/" .. outputconfigname
outputbindirproj = outputbindir .. "/%{prj.name}"
outputintdirproj = outputintdir .. "/%{prj.name}"
outputbindirproj = outputbindir
outputintdirproj = outputintdir


function createbaseprojectcpp(name, type)
    project (name)
	    kind (type)
        language "C++"
        cppdialect "C++latest"
        staticruntime "Off"

        targetdir (outputbindirproj)
        objdir (outputintdirproj)

        files
        {
            "Source/**.h",
            "Source/**.cpp",
            "Source/**.hpp",
        }
        
        includedirs
        {
            "Source",
        }

        flags
        {
            "MultiProcessorCompile",
            "UndefinedIdentifiers",
	    }
	
        filter "configurations:Debug"
            defines { "POG_DEBUG", "POG_ENABLE_ASSERT" }
            runtime "Debug"
            symbols "On"

        filter "configurations:Release"
            defines { "POG_RELEASE", "POG_ENABLE_VERIFY" }
            runtime "Release"
            optimize "On"

        filter "configurations:Dist"
            defines "POG_DIST"
            runtime "Release"
            optimize "On"

            flags
            {
                "LinkTimeOptimization"
	        }

    project (name)
end


-- https://github.com/premake/premake-core/issues/1061

require('vstudio')
premake.api.register {
  name = "solutionitems",
  scope = "workspace",
  kind = "list:keyed:list:string",
}

premake.override(premake.vstudio.sln2005, "projects", function(base, wks)
    for _, folder in ipairs(wks.solutionitems) do
      for name, files in pairs(folder) do
        premake.push('Project("{2150E333-8FDC-42A3-9474-1A3956D46DE8}") = "'..name..'", "'..name..'", "{' .. os.uuid("Solution Items:"..wks.name) .. '}"')
        premake.push("ProjectSection(SolutionItems) = preProject")
        for _, file in ipairs(files) do
          file = path.rebase(file, ".", wks.location)
          premake.w(file.." = "..file)
        end
        premake.pop("EndProjectSection")
        premake.pop("EndProject")
      end
    end
  base(wks)
end)