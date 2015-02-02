local GCC_AVR_CC_PATH = "avr-gcc"
local GCC_AVR_CPP_PATH = "avr-g++"
local GCC_AVR_AR_PATH = "avr-ar"

premake.gcc.cc = GCC_AVR_CC_PATH
premake.gcc.cxx = GCC_AVR_CPP_PATH
premake.gcc.ar = GCC_AVR_AR_PATH

solution "yalla"

--------------------------------------------------------------------------------
-- Command line options
--------------------------------------------------------------------------------

newoption {
  trigger     = "mmcu",
  description = "Chose the target platform (default = atmega8)",
  value="MMCU",
  allowed = {
    { "atmega8",  "ATmega8" },
    { "test",  "Test" }
  }
}

newoption {
  trigger     = "fcpu",
  description = "Specify the CPU frequency (default = 8000000)",
  value="FCPU"
}

--------------------------------------------------------------------------------
-- Premake settings
--------------------------------------------------------------------------------

location "build"
language "C++"
kind "ConsoleApp"

--------------------------------------------------------------------------------
-- General build settings
--------------------------------------------------------------------------------

-- Includes
includedirs { "include", "include/yalla", "include/yalla/device/atmega8", "/usr/include/simavr/avr/"}
-- Enables some additional warnings.
buildoptions { "-Wall" }
-- Enables C++11 support.
buildoptions { "-std=c++14" }
-- set optimization.
buildoptions { "-Os " }
-- set AVR specific options
buildoptions {"-fshort-enums -funsigned-char -funsigned-bitfields"}

if _OPTIONS["mmcu"] then
  buildoptions { "-mmcu=" .. _OPTIONS["mmcu"] }
end

if _OPTIONS["fcpu"] then
  defines { "F_CPU=" .. _OPTIONS["fcpu"] }
end

--------------------------------------------------------------------------------
-- Configurations
--------------------------------------------------------------------------------
configurations { "release", "debug" }

configuration "release"
  objdir "build/bin/obj"
  targetdir "build/bin"

configuration "debug"
  objdir "build/dbg/obj"
  targetdir "build/dbg"

--------------------------------------------------------------------------------
-- Projects
--------------------------------------------------------------------------------
project "iomm"
  files { "src/test/avr/iomm/iomm.cpp", "src/test/avr/iomm/iomm_trace.c" }
  targetname (project().name .. ".elf")
  postbuildcommands { "avr-objcopy -O ihex bin/" .. project().name .. ".elf bin/"  .. project().name .. ".hex"}
  postbuildcommands { "avr-size bin/" .. project().name .. ".elf"}

project "register"
  files { "src/test/avr/register/register.cpp", "src/test/avr/register/register_trace.c" }
  targetname (project().name .. ".elf")
  postbuildcommands { "avr-objcopy -O ihex bin/" .. project().name .. ".elf bin/"  .. project().name .. ".hex"}
  postbuildcommands { "avr-size bin/" .. project().name .. ".elf"}

-- Add new projects here

-- Template:
-- project "<name>"
--   files { "<file>" }
--   targetname (project().name .. ".elf")
--   postbuildcommands { "avr-objcopy -O ihex bin/" .. project().name .. ".elf bin/"  .. project().name .. ".hex"}
--   postbuildcommands { "avr-size bin/" .. project().name .. ".elf"}
