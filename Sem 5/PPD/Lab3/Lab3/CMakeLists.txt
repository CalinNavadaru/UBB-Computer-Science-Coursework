cmake_minimum_required(VERSION 3.29)
project(Laborator3)

set(CMAKE_CXX_STANDARD 20)

# Find MPI package
find_package(MPI REQUIRED)

# Add include directories for MPI
include_directories(${MPI_INCLUDE_PATH})

add_executable(Laborator3 main.cpp)

target_link_libraries(Laborator3 ${MPI_LIBRARIES})

set(CMAKE_PREFIX_PATH "/usr/bin/mpirun -c 2")

