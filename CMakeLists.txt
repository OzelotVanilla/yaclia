project("yaclia")
cmake_minimum_required(VERSION 3.22)
enable_testing()

# Compile options
add_compile_options(-enable-pretty-printing)

# Define directory into variable
aux_source_directory(util Util)
aux_source_directory(window Window)

# Relate variable to different option of building project
set(StandardYacliaOption ${Util} ${Window})

# Final excutables
add_executable(yaclia head.h ${StandardYacliaOption} main.cc)