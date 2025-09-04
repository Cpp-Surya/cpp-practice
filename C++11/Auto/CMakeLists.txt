cmake_minimum_required(VERSION 3.10)
project(AutoStorageClass)

#Set C++ standard
#This program includes features supported by C++11/14/17/20 for better convenience using C++20 standard to cover all features.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "C++ Standard set to: ${CMAKE_CXX_STANDARD}")

#Include directory for header files
#include_directories(${PROJECT_SOURCE_DIR}/inc)

#Add source files
#file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

#Create executable
add_executable(main main.cpp)

#Link any additional libraries here if needed
#target_link_libraries(StringToDataConverter aditional_library)