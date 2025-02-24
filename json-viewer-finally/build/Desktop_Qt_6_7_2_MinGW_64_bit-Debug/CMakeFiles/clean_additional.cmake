# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\json-viewer-finally_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\json-viewer-finally_autogen.dir\\ParseCache.txt"
  "json-viewer-finally_autogen"
  )
endif()
