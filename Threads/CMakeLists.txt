cmake_minimum_required(VERSION 3.10)
project(Threads)

#Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Include directory for header files
#include_directories(${PROJECT_SOURCE_DIR}/inc)

#Add source files
#file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

#Create executable
add_executable(ThreadBasics ThreadBasics.cpp)

#Link any additional libraries here if needed
#target_link_libraries(StringToDataConverter aditional_library)