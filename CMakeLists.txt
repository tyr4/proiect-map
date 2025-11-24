cmake_minimum_required(VERSION 3.16)
project(MAP_ascii_from_image)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)

find_package(OpenCV REQUIRED core imgproc imgcodecs)

add_executable(MAP_ascii_from_image src/main.cpp
        src/ascii.cpp
        include/ascii.hpp)

target_link_libraries(MAP_ascii_from_image PRIVATE
        opencv_core
        opencv_imgproc
        opencv_imgcodecs
)
target_include_directories(MAP_ascii_from_image PRIVATE include)

# Precompiled header for OpenCV
target_precompile_headers(MAP_ascii_from_image PRIVATE
        <opencv2/core.hpp>
        <opencv2/imgproc.hpp>
        <opencv2/imgcodecs.hpp>
)
