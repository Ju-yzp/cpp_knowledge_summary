cmake_minimum_required(VERSION 3.10)
project(cpp_summary)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#############
## COMPILE ##
#############

set(COMPILE_DIR "${PROJECT_SOURCE_DIR}")

file(GLOB CPP_FILES "${COMPILE_DIR}/*/*.cpp")

foreach(CPP_FILE ${CPP_FILES})
    get_filename_component(PREFIX ${CPP_FILE} NAME_WE)
    set(FILE_PREFIX ${PREFIX})
    
    add_executable(${FILE_PREFIX} ${CPP_FILE})

    install(TARGETS ${FILE_PREFIX}
            DESTINATION lib/${PROJECT_NAME}) 
endforeach()