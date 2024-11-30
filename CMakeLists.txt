cmake_minimum_required(VERSION 3.27)

project(simple_vector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra -fmax-errors=5")

set(PROJECT_NAME_LIB "${CMAKE_PROJECT_NAME}_lib") # for add_lib in test cmake
add_subdirectory(simple_vector_lib)

enable_testing()
add_subdirectory(test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME_LIB})