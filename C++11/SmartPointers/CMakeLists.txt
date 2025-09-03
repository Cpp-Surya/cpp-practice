cmake_minimum_required(VERSION 3.10)
project(SmartPointers)

#Set C++ standard
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
#message(STATUS "C++ Standard set to: ${CMAKE_CXX_STANDARD}")

#Include directory for header files
#include_directories(${PROJECT_SOURCE_DIR}/inc)

#Add source files
#file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

#Create executable
add_executable(UniquePtr UniquePtr.cpp)
set_property(TARGET UniquePtr PROPERTY CXX_STANDARD 14)
add_executable(SharedPtr SharedPtr.cpp)
set_property(TARGET SharedPtr PROPERTY CXX_STANDARD 11)
add_executable(WeakPtr WeakPtr.cpp)
set_property(TARGET WeakPtr PROPERTY CXX_STANDARD 11)

#Link any additional libraries here if needed
#target_link_libraries(StringToDataConverter aditional_library)