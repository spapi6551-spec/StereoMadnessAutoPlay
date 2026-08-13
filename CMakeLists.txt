cmake_minimum_required(VERSION 3.21)
project(StereoMadnessAutoPlay VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "GEODE_SDK is not set. Install the Geode CLI/SDK and set GEODE_SDK.")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_BINARY_DIR}/geode)
setup_geode_mod(${PROJECT_NAME})
