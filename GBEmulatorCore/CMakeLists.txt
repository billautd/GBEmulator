add_library(GBEmulatorCore SHARED)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
set_target_properties(GBEmulatorCore PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
target_compile_definitions(GBEmulatorCore PRIVATE CORE_EXPORTS)
target_sources(GBEmulatorCore
	PRIVATE
		lib/Cartridge.cpp
		lib/Common.cpp
		lib/Context.cpp
		lib/CPU.cpp
		lib/Emulator.cpp
		lib/PPU.cpp
		lib/Registers.cpp
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS
			include
		FILES
			include/Cartridge.h
			include/Common.h
			include/Context.h
			include/CPU.h
			include/Emulator.h
			include/PPU.h
			include/Registers.h
)
target_include_directories(GBEmulatorCore PUBLIC include)
target_link_libraries(GBEmulatorCore PUBLIC SDL3::SDL3)
target_link_libraries(GBEmulatorCore PUBLIC SDL3_ttf::SDL3_ttf)