# Config about compilation 
project("yaclia - One Window Test Program")
cmake_minimum_required(VERSION 3.22)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++20")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
enable_testing()

# Compile options
add_compile_options(-enable-pretty-printing)

# Define directory into variable

# Relate variable to different option of building project

# Final excutables
add_executable(test_one_window main.cc)