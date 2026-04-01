cmake_minimum_required(VERSION 3.29)
project(Cplusplus)

set(CMAKE_CXX_STANDARD 20)

add_executable(Cplusplus main.cpp)
set_source_files_properties(
        main.cpp
        PROPERTIES
        COMPILE_OPTIONS "-O3"
)