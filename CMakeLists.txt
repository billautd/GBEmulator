cmake_minimum_required(VERSION 3.23)

project(GBEmulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_BUILD_TYPE Debug)

# set options before add_subdirectory
option(TRACY_ENABLE "" ON)
option(TRACY_ON_DEMAND "" ON)
add_subdirectory(deps/Tracy/tracy-0.13.1)  # target: TracyClient or alias Tracy::TracyClient
add_subdirectory(GBEmulatorCore)
add_subdirectory(GBEmulator)
add_subdirectory(GBEmulatorTests)