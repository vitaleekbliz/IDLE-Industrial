-- premake5.lua
workspace "IDLE Industial"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

--Windows copy dependencies
   filter "system:windows"
      -- {COPY} is a Premake token, but for complex folder structures, 
      -- standard shell commands are often more reliable.
      postbuildcommands {
         -- Copy all DLLs from the dependency folders to the target directory
         "{COPYDIR} \"%{wks.location}/Vendor/SDL3/SDL3-3.4.0/lib/x64/*.dll\" \"%{cfg.targetdir}\"",
         "{COPYDIR} \"%{wks.location}/Vendor/SDL3/SDL3_image-3.4.0/lib/x64/*.dll\" \"%{cfg.targetdir}\"",
         "{COPYDIR} \"%{wks.location}/Vendor/SDL3/SDL3_ttf-3.2.2/lib/x64/*.dll\" \"%{cfg.targetdir}\"",
         "{COPYDIR} \"%{wks.location}/Vendor/SDL3/SDL3_mixer-3.2.0/lib/x64/*.dll\" \"%{cfg.targetdir}\"",
         
         -- Copy your Assets folder (assumes Assets is in your project root)
         -- Using xcopy style logic to ensure the folder structure is maintained
         "IF EXIST \"%{wks.location}/Assets\" (xcopy /Q /E /Y /I \"%{wks.location}/Assets\" \"%{cfg.targetdir}/Assets\")"
      }
   
   --Linux copy dependencies
   filter "system:linux"
      postbuildcommands {
         -- Ensure the target directory and Assets folder exist
         "mkdir -p \"%{cfg.targetdir}/Assets\"",

         -- Copy all shared objects (.so) from the dependency folders
         "cp -f \"%{wks.location}/Vendor/SDL3/SDL3-3.4.0/lib/x64/\"*.so* \"%{cfg.targetdir}/\"",
         "cp -f \"%{wks.location}/Vendor/SDL3/SDL3_image-3.4.0/lib/x64/\"*.so* \"%{cfg.targetdir}/\"",
         "cp -f \"%{wks.location}/Vendor/SDL3/SDL3_ttf-3.2.2/lib/x64/\"*.so* \"%{cfg.targetdir}/\"",
         "cp -f \"%{wks.location}/Vendor/SDL3/SDL3_mixer-3.2.0/lib/x64/\"*.so* \"%{cfg.targetdir}/\"",
         
         -- Copy Assets folder content
         "cp -rb \"%{wks.location}/PingPongLite/Assets/\"* \"%{cfg.targetdir}/Assets/\""
      }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"


group "Engine"
   include "Engine/Build-Engine.lua"
group ""

include "App/Build-App.lua"

group "Configuration"
   project "ProjectFiles"
      kind "None"
      files { ".clang-format", ".gitignore", "README.md", "**.lua", }
      vpaths { ["Solution Items/*"] = { "*" } }
group ""

   