add_executable(GBEmulator main.cpp)

set_target_properties(GBEmulator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
target_compile_features(GBEmulator PRIVATE cxx_std_20)
target_link_libraries(GBEmulator PRIVATE GBEmulatorCore)