cmake_minimum_required(VERSION 3.10)
project(Threads)

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
add_executable(ThreadBasics ThreadBasics.cpp)
add_executable(ThreadNativeHandle ThreadNativeHandle.cpp)
add_executable(ThreadsClass ThreadsClass.cpp)
add_executable(ThreadLockGuard ThreadLockGuard.cpp)
add_executable(ThreadUniqueLock ThreadUniqueLock.cpp)
add_executable(ThreadAtomics ThreadAtomics.cpp)
add_executable(ThreadSharedLock ThreadSharedLock.cpp)
add_executable(ThreadPool ThreadPool.cpp)
#Link any additional libraries here if needed
#target_link_libraries(StringToDataConverter aditional_library)