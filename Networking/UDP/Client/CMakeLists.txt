cmake_minimum_required(VERSION 3.10)
project(UDP-Server-Client)

#Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Include directory for header files
#include_directories(${PROJECT_SOURCE_DIR}/inc)

#Add source files
#file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
# Add debug flags
set(CMAKE_BUILD_TYPE Debug)

#Create executable
add_executable(UDPClient UDP_Client.cpp)
#Link any additional libraries here if needed
#target_link_libraries(StringToDataConverter aditional_library)