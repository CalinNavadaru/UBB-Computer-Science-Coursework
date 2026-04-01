cmake_minimum_required(VERSION 3.24)
project(lab01_pb10 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab01_pb10 main.c)

target_link_libraries(lab01_pb10 m)