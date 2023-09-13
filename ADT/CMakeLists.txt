cmake_minimum_required(VERSION 3.5)

file(
    GLOB_RECURSE
    HEADER_FILE_SET
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*
)

file(
    GLOB_RECURSE
    SOURCE_FILE_SET
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(ADT STATIC ${SOURCE_FILE_SET})
