project(fidel)
cmake_minimum_required(VERSION 2.6)
add_subdirectory(src)

set(CMAKE_C_FLAGS "-Wall -g")
set_target_properties(fidel PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
