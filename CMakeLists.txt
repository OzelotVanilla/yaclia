# Config about compilation 
project("yaclia")
cmake_minimum_required(VERSION 3.22)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++20")
if (UNIX)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
endif (UNIX)
enable_testing()

# Compile options
add_compile_options(-enable-pretty-printing)

# Define directory into variable
aux_source_directory(system SystemDirSelf)
aux_source_directory(system/signal SystemSignal)
aux_source_directory(util Util)
aux_source_directory(util/observer_pattern ObserverPattern)
aux_source_directory(view/container ViewContainer)
aux_source_directory(view/manager ViewManager)
set(SystemDir ${SystemDirSelf} ${SystemSignal})
set(View ${ViewContainer} ${ViewManager})

# Relate variable to different option of building project
set(StandardYacliaOption ${SystemDir} ${ObserverPattern} ${Util} ${View})

# Final excutables
add_executable(yaclia head.h ${StandardYacliaOption} main.h main.cc)

# Link to `ncurses`
target_link_libraries(yaclia ${CURSES_LIBRARIES})