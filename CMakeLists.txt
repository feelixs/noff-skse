cmake_minimum_required(VERSION 3.21)

project(
    noff
    VERSION 1.4.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed.")
endif()

set(CommonLibSSE_DIR "" CACHE PATH "Path to CommonLibSSE-NG source tree")
if(NOT CommonLibSSE_DIR)
    # Default to sibling directory
    set(CommonLibSSE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../CommonLibSSE-NG")
endif()

if(NOT EXISTS "${CommonLibSSE_DIR}/CMakeLists.txt")
    message(FATAL_ERROR "CommonLibSSE-NG not found at ${CommonLibSSE_DIR}. "
        "Set -DCommonLibSSE_DIR=<path> or clone it next to this project.")
endif()

set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory("${CommonLibSSE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/CommonLibSSE" EXCLUDE_FROM_ALL)
include("${CommonLibSSE_DIR}/cmake/CommonLibSSE.cmake")

add_commonlibsse_plugin(${PROJECT_NAME}
    SOURCES
        src/main.cpp
)

target_precompile_headers(${PROJECT_NAME}
    PRIVATE src/pch.h
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        /W4
        /WX
        /permissive-
        /Zc:preprocessor
)

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION "SKSE/Plugins"
)
