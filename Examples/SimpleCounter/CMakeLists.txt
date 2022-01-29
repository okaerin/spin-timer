# Simple Counter Example
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(PROJECT_NAME "SimpleCounter")
project(${PROJECT_NAME} 
        VERSION 1.0.0
        LANGUAGES CXX
        DESCRIPTION "Basic usage of the SpinTimer")

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} SpinTimerLib)