cmake_minimum_required(VERSION 3.14)
project(OS)

set(CMAKE_CXX_STANDARD 14)

find_package (Threads)

add_executable(OS main.cpp)

target_link_libraries (OS ${CMAKE_THREAD_LIBS_INIT})