cmake_minimum_required(VERSION 2.8.9)
project(BezitkGenerator)
file(GLOB_RECURSE SOURCE_FILES "ConsoleApplication1/*.hpp" "ConsoleApplication1/*.cpp")
add_executable(Generator ${SOURCE_FILES})