cmake_minimum_required(VERSION 2.8.9)
project(BezitkGenerator)
file(GLOB_RECURSE SOURCE_FILES "src/*.hpp" "src/*.cpp")
add_executable(Generator ${SOURCE_FILES})
