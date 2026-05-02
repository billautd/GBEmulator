cmake_minimum_required(VERSION 3.23)

project(GBEmulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(GBEmulatorCore)
add_subdirectory(GBEmulator)
#add_subdirectory(GBEmulatorTests)