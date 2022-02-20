# Spin-Timer Lib
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

#set C++ specifics
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include git to determine version
set(PROJECT_NAME "SpinTimer")
project(${PROJECT_NAME}
        VERSION 3.0.1
		LANGUAGES CXX
		DESCRIPTION "OOP Timer scheduler")

# Include own cmake modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(Documentation)

# options
option(${PROJECT_NAME}_BUILD_EXAMPLES "build cli example" OFF)

# Names of needed components
set(${PROJECT_NAME}_INC_DIR "${PROJECT_SOURCE_DIR}/include")
set(${PROJECT_NAME}_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE INC_FILES "${${PROJECT_NAME}_INC_DIR}/*.h")
file(GLOB_RECURSE SRC_FILES "${${PROJECT_NAME}_SRC_DIR}/*.cpp")

# Make the main target
add_library(${PROJECT_NAME}Lib ${SRC_FILES} ${INC_FILES})
target_include_directories(${PROJECT_NAME}Lib PUBLIC ${${PROJECT_NAME}_INC_DIR})

# build optional things
if(${PROJECT_NAME}_BUILD_EXAMPLES)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Examples/SimpleCounter)
endif()