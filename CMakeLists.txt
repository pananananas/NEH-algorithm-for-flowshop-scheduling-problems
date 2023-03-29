cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME zaj3)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)

# add all source files in src folder
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

# add all header files in include folder
include_directories(inc)

# add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})