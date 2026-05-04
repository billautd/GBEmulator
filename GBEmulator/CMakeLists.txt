add_executable(GBEmulator main.cpp)

set_target_properties(GBEmulator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
target_link_libraries(GBEmulator PRIVATE GBEmulatorCore)