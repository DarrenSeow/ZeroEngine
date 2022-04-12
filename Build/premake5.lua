workspace "ZeroEngine"            -- Solution
    location "ZeroEngine"         -- Create Solution in "PotatoEngine" folder
	architecture "x64"
	startproject "ZeroEditor"
	cppdialect "C++20"
	configurations
	{
		"Debug",
		"Release"
	}

-- Type Aliases
outputdir       = "../Bin/%{prj.name}"
objOutputDir    = "../Bin-int/"
sourceFilesPath = "../Src/%{prj.name}"
engineFilesPath = "../Src/ZeroEngine"
------ Include Directories -------------------------------------------
IncludeDir = {}
IncludeDir["Vulkan"]          = "$(Vulkan_SDK)/Include"
IncludeDir["glm"]			  = "../Bin/glm/glm"
------ ZeroEngine -------------------------------------------
project "ZeroEngine"
	location (sourceFilesPath) 
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
    warnings "Extra"
	staticruntime "on"
    characterset "MBCS"
	targetname "ZeroEngine"
	editAndContinue "Off" 

    targetdir ( outputdir )
    objdir    ( objOutputDir )

	pchheader "pch.h"
	pchsource "../Src/%{prj.name}/Pch/pch.cpp"

    -- Adding Files into project
	files
	{
		sourceFilesPath .. "/**.h",
        sourceFilesPath .. "/**.hpp",
		sourceFilesPath .. "/**.cpp",
        sourceFilesPath .. "/**.rc",
        sourceFilesPath .. "/**.ico",
	}
    
    -- Adding Filters into project (to be edited)
    vpaths
    {
        ["*"] = { "**.h", "**.hpp", "**.cpp", "**.rc", "**.ico"}
    }

    -- Include Directories under C/C++ General
	includedirs
	{
        -- Internal Source Files
		sourceFilesPath .. "/Pch",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.glm}"
	}
    
    -- Prepocessor defines
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"NOMINMAX",
		"ZE_PLATFORM_WINDOWS"
	}
	
    -- Build Flags for compiling / linking
	flags
	{
		"MultiProcessorCompile"
	}
	postbuildcommands
	{
		"{mkdir} Data",
		"{copy} ../Data ../../Bin/Data",

		
	}
    -- Properties under "All" Configuration
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ZE_PLATFORM_WINDOWS"
		}

    -- Properties under "Debug" Configuration
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		linkoptions{"/NODEFAULTLIB:libcmt.lib"}

		defines
		{
			"ZE_DEBUG",
			"_DEBUG"
		}

    -- Properties under "Release" Configuration
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		
		defines
		{
			"ZE_RELEASE",
			"NDEBUG"
		}


------ ZeroEditor -------------------------------------------
project "ZeroEditor"
	location (sourceFilesPath) 
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
    warnings "Extra"
	staticruntime "on"
    characterset "MBCS"
	targetname "ZeroEditor"
	editAndContinue "Off" 

    targetdir ( outputdir )
    objdir    ( objOutputDir )

	pchheader "pch.h"
	pchsource "../Src/%{prj.name}/Pch/pch.cpp"

    -- Adding Files into project
	files
	{
		sourceFilesPath .. "/**.h",
        sourceFilesPath .. "/**.hpp",
		sourceFilesPath .. "/**.cpp",
        sourceFilesPath .. "/**.rc",
        sourceFilesPath .. "/**.ico",
	}
    
    -- Adding Filters into project (to be edited)
    vpaths
    {
        ["*"] = { "**.h", "**.hpp", "**.cpp", "**.rc", "**.ico"}
    }

    -- Include Directories under C/C++ General
	includedirs
	{
        -- Internal Source Files
		sourceFilesPath .. "/Pch",
		
		engineFilesPath .. "/Application",
		"%{IncludeDir.Vulkan}"
	}
    
    -- Prepocessor defines
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"NOMINMAX",
		"ZE_PLATFORM_WINDOWS"
	}
	
    -- Build Flags for compiling / linking
	flags
	{
		"MultiProcessorCompile"
	}
	-- Linking of lib files
	libdirs 
	{
		outputdir,
		"$(VULKAN_SDK)/LIB"
	}

	links
	{		
		"ZeroEngine",
		"vulkan-1.lib",
	}
    -- Properties under "All" Configuration
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ZE_PLATFORM_WINDOWS"
		}

    -- Properties under "Debug" Configuration
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		linkoptions{"/NODEFAULTLIB:libcmt.lib"}

		defines
		{
			"ZE_DEBUG",
			"_DEBUG"
		}

    -- Properties under "Release" Configuration
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		
		defines
		{
			"ZE_RELEASE",
			"NDEBUG"
		}
