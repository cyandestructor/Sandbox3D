workspace "Jass"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Jass"
	location "Jass"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/".. outputdir .. "/%{prj.name}")
	objdir ("bin-int/".. outputdir .. "/%{prj.name}")

	pchheader "jasspch.h"
	pchsource "Jass/src/jasspch.cpp"

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { "%{prj.name}/vendor/spdlog/include", "Jass/src" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines { "JASS_PLATFORM_WINDOWS", "JASS_BUILD_DLL" }

	filter "configurations:Debug"
		defines "JASS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "JASS_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "JASS_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/".. outputdir .. "/%{prj.name}")
	objdir ("bin-int/".. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { "Jass/vendor/spdlog/include", "Jass/src" }

	links { "Jass" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines { "JASS_PLATFORM_WINDOWS" }

		postbuildcommands { "{COPY} ../bin/" .. outputdir .. "/Jass/Jass.dll %{cfg.buildtarget.directory}" }

	filter "configurations:Debug"
		defines "JASS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "JASS_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "JASS_DIST"
		optimize "On"