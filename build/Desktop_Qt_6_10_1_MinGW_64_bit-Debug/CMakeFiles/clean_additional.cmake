# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QtExplorer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QtExplorer_autogen.dir\\ParseCache.txt"
  "QtExplorer_autogen"
  )
endif()
