# Simple Counter Example
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# set C++ specifics
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME "SimpleCounter")
project(${PROJECT_NAME} 
        VERSION 1.0.0
        LANGUAGES CXX
        DESCRIPTION "Basic usage of the SpinTimer")

# Include own cmake modules

# options

# Names of needed components
set(${PROJECT_NAME}_INC_DIR "${PROJECT_SOURCE_DIR}/include")
set(${PROJECT_NAME}_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE ${PROJECT_NAME}_INC_FILES "${${PROJECT_NAME}_INC_DIR}/*.h")
file(GLOB_RECURSE ${PROJECT_NAME}_SRC_FILES "${${PROJECT_NAME}_SRC_DIR}/*.cpp")

# Make the main target
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRC_FILES} ${${PROJECT_NAME}_INC_FILES})
target_link_libraries(${PROJECT_NAME} SpinTimerLib)
target_include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INC_DIR})

# build optional things