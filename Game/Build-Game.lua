project "Game"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   --Precompiled headers
   pchheader "pchGame.h"
   pchsource "Source/pchGame.cpp"

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
      -- standard shell commands are often more reliable.
      postbuildcommands {
         -- Copy all DLLs from the dependency folders to the target directory
         "{COPYDIR} \"%{wks.location}/Vendor/SDL3/SDL3-3.4.0/lib/x64/*.dll\" \"%{cfg.targetdir}\"",
         "{COPYDIR} \"%{wks.location}/Vendor/SDL3/SDL3_image-3.4.0/lib/x64/*.dll\" \"%{cfg.targetdir}\"",
         "{COPYDIR} \"%{wks.location}/Vendor/SDL3/SDL3_ttf-3.2.2/lib/x64/*.dll\" \"%{cfg.targetdir}\"",
         "{COPYDIR} \"%{wks.location}/Vendor/SDL3/SDL3_mixer-3.2.0/lib/x64/*.dll\" \"%{cfg.targetdir}\"",
         
         -- Copy your Assets folder (assumes Assets is in your project root)
         "IF EXIST \"%{wks.location}/Assets\" (xcopy /Q /E /Y /I \"%{wks.location}/Assets\" \"%{cfg.targetdir}/Assets\")"
      }

      --Linux copy dependencies
   ---filter "system:linux"
   ---   postbuildcommands {
   ---      -- Ensure the target directory and Assets folder exist
   ---      "mkdir -p \"%{cfg.targetdir}/Assets\"",
   ---
   ---      -- Copy all shared objects (.so) from the dependency folders
   ---      "cp -f \"%{wks.location}/Vendor/SDL3/SDL3-3.4.0/lib/x64/\"*.so* \"%{cfg.targetdir}/\"",
   ---      "cp -f \"%{wks.location}/Vendor/SDL3/SDL3_image-3.4.0/lib/x64/\"*.so* \"%{cfg.targetdir}/\"",
   ---      "cp -f \"%{wks.location}/Vendor/SDL3/SDL3_ttf-3.2.2/lib/x64/\"*.so* \"%{cfg.targetdir}/\"",
   ---      "cp -f \"%{wks.location}/Vendor/SDL3/SDL3_mixer-3.2.0/lib/x64/\"*.so* \"%{cfg.targetdir}/\"",
   ---      
   ---      -- Copy Assets folder content
   ---      "cp -rb \"%{wks.location}/PingPongLite/Assets/\"* \"%{cfg.targetdir}/Assets/\""
   ---   }

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