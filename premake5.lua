
-- defines our entire workspace as our solution in VS
workspace "Orca"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Sandbox"


-- Defines the main output dir for files in Hazel/.../bin and Hazel/.../bin-int
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Orca/vendor/GLFW/include"
IncludeDir["Glad"] = "Orca/vendor/Glad/include"
IncludeDir["imgui"] = "Orca/vendor/imgui"
IncludeDir["glm"] = "Orca/vendor/glm"

group "Dependencies"

	include "Orca/vendor/GLFW"
	include "Orca/vendor/GLAD"
	include "Orca/vendor/imgui"

group ""

project "Orca"
	location "Orca"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "oapch.h"
	pchsource "Orca/src/oapch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"

	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW", "Glad", "imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"OA_PLATFORM_WINDOWS",
			"OA_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "OA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "OA_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OA_DIST"
		runtime "Release"
		optimize "on"




project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	

	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Orca/vendor/spdlog/include",
		"Orca/src",
		"%{IncludeDir.glm}",
		"Orca/vendor"
	}

	links {
		"Orca"
	}

	filter "system:windows"
		systemversion "latest"
		defines {
			"OA_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "OA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "OA_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OA_DIST"
		runtime "Release"
		optimize "on"