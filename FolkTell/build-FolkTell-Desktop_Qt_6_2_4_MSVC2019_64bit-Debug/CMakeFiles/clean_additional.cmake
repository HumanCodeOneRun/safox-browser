# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FolkTell_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FolkTell_autogen.dir\\ParseCache.txt"
  "FolkTell_autogen"
  )
endif()
