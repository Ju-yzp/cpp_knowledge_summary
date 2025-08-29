cmake_minimum_required(VERSION 3.10)
project(cpp_summary)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ##############################################################################
# COMPILE ##
# ##############################################################################

set(COMPILE_DIR "${PROJECT_SOURCE_DIR}")

file(GLOB cpp_files "${COMPILE_DIR}/*/*.cpp")

foreach(cpp_file ${cpp_files})
  get_filename_component(PREFIX ${cpp_file} NAME_WE)
  set(FILE_PREFIX ${PREFIX})

  add_executable(${FILE_PREFIX} ${cpp_file})

  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${FILE_PREFIX} PRIVATE -O0)
    target_compile_options(${FILE_PREFIX} PRIVATE -fno-unroll-loops)
    target_compile_options(${FILE_PREFIX} PRIVATE -fno-vectorize)
    target_compile_options(${FILE_PREFIX} PRIVATE -fno-slp-vectorize)
  endif()

  install(TARGETS ${FILE_PREFIX} DESTINATION lib/${PROJECT_NAME})
endforeach()
