# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\acoustic-calibrator-terminal_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\acoustic-calibrator-terminal_autogen.dir\\ParseCache.txt"
  "acoustic-calibrator-terminal_autogen"
  )
endif()
