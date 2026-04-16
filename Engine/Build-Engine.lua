project "Engine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",

      --Boost
      "../Vendor/Boost/include",

      -- SDL3 Core
      "../Vendor/SDL3/SDL3-3.4.0/include",

      -- SDL3 Extensions
      "../Vendor/SDL3/SDL3_image-3.4.0/include",
      "../Vendor/SDL3/SDL3_mixer-3.2.0/include",
      "../Vendor/SDL3/SDL3_ttf-3.2.2/include"
   }

   libdirs{
      -- Search paths for the .lib files
      "../Vendor/SDL3/SDL3-3.4.0/lib/x64",
      "../Vendor/SDL3/SDL3_image-3.4.0/lib/x64",
      "../Vendor/SDL3/SDL3_mixer-3.2.0/lib/x64",
      "../Vendor/SDL3/SDL3_ttf-3.2.2/lib/x64"
   }

      -- Libraries to link against
   links { 
      "SDL3", 
      "SDL3_image", 
      "SDL3_ttf", 
      "SDL3_mixer" 
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

   filter "configurations:Debug"
       libdirs { "../Vendor/Boost/libs/Debug" }
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       libdirs { "../Vendor/Boost/libs/Debug" }
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       libdirs { "../Vendor/Boost/libs/Release" }
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"