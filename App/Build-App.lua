project "App"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   --Precompiled headers
   pchheader "pchApp.h"
   pchsource "Source/pchApp.cpp"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",

      --Boost
      --"../Vendor/Boost/include",

	  -- Include Engine
	  "../Engine/Source"
   }

   links
   {
      "Engine"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       --libdirs { "../Vendor/Boost/libs/Debug" }
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       --libdirs { "../Vendor/Boost/libs/Debug" }
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       --libdirs { "../Vendor/Boost/libs/Release" }
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"