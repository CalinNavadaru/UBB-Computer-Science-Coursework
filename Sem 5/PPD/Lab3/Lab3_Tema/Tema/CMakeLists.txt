cmake_minimum_required(VERSION 3.29)
project(Tema)

set(CMAKE_CXX_STANDARD 20)

# Find MPI package
find_package(MPI REQUIRED)

# Add include directories for MPI
include_directories(${MPI_INCLUDE_PATH})

add_executable(Tema varianta3.cpp
)
target_link_libraries(Tema ${MPI_LIBRARIES})

set(CMAKE_PREFIX_PATH "/usr/bin/mpirun")
