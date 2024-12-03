cmake_minimum_required(VERSION 3.27)

set(PROJECT_NAME_LIB "${CMAKE_PROJECT_NAME}_lib")

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

add_library(${PROJECT_NAME_LIB} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME_LIB} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
                                               PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")