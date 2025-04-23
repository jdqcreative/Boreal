workspace "Boreal"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Boreal/vendor/GLFW/include"

include "Boreal/vendor/GLFW"

project "Boreal"
	location "Boreal"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bopch.h"
	pchsource "Boreal/src/bopch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/**.h",
		"%{prj.name}/vendor/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/pinelog",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "on"
		systemversion "latest"

		defines 
		{
			"BO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BO_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "BO_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "BO_DIST"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/pinelog",
		"Boreal/src"
	}

	links
	{
		"Boreal"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "on"
		systemversion "latest"

		defines 
		{
			"BO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BO_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "BO_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "BO_DIST"
		optimize "on"