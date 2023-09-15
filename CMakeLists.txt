cmake_minimum_required(VERSION 3.5)

project(test)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Basic)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ADT)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Socket)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/XML)

add_executable(test test.c)

target_link_libraries(test XML Basic ADT)
