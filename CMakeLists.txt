cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(c)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")
add_executable(main "${SOURCES}")
target_link_libraries(main)
