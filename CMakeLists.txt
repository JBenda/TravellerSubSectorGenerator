cmake_minimum_required(VERSION 3.15)
project(BezitkGenerator)


file(GLOB_RECURSE SOURCE_FILES "src/*.hpp" "src/*.cpp")

add_executable(Generator ${SOURCE_FILES})
set_property(TARGET Generator PROPERTY CXX_STANDARD 20)

find_package(SFML REQUIRED system window graphics)
target_link_libraries(Generator sfml-window sfml-graphics)

