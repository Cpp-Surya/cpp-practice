cmake_minimum_required(VERSION 3.10)
project(LinkedListOperations)

#Set C++ standard
set(CMAKE_CXX_STANDARD 11)
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