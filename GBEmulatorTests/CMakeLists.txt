add_executable(GBEmulatorTests)

find_package(Catch2 REQUIRED)
set_target_properties(GBEmulatorTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
target_sources(GBEmulatorTests
PRIVATE
	lib/Registers/RegistersTests.cpp
    lib/CPU/CPUTests.cpp
    lib/CPU/CPUTests_nop.cpp
    lib/CPU/CPUTests_ld_r16_imm16.cpp
    lib/CPU/CPUTests_ld_r16mem_a.cpp
)
target_compile_features(GBEmulatorTests PRIVATE cxx_std_20)
target_include_directories(GBEmulatorTests PRIVATE include)
target_link_libraries(GBEmulatorTests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(GBEmulatorTests PRIVATE GBEmulatorCore)