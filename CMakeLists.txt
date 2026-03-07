cmake_minimum_required(VERSION 3.21)

project(
    noff
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed.")
endif()

find_package(CommonLibSSE CONFIG REQUIRED)

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
