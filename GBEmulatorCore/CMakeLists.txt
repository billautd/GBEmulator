add_library(GBEmulatorCore SHARED)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
set_target_properties(GBEmulatorCore PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
target_compile_definitions(GBEmulatorCore PRIVATE CORE_EXPORTS)
target_compile_definitions(GBEmulatorCore PRIVATE TRACY_ENABLE)
target_sources(GBEmulatorCore
	PRIVATE

		lib/Common.cpp
		lib/Cartridge.cpp
		lib/Context.cpp
		lib/CPU.cpp
		lib/CPUMicroOp.cpp
		lib/DMA.cpp
		lib/Emulator.cpp
		lib/Interrupts.cpp
		lib/Joypad.cpp
		lib/Mem.cpp
		lib/PPU.cpp
		lib/Registers.cpp
		lib/UI.cpp
	PUBLIC
		FILE_SET main
		TYPE HEADERS
		BASE_DIRS
			include
		FILES
			include/Common.h
			include/Cartridge.h
			include/Context.h
			include/CPU.h
			include/CPUMicroOp.h
			include/DMA.h
			include/Emulator.h
			include/Interrupts.h
			include/Joypad.h
			include/Mem.h
			include/PPU.h
			include/Registers.h
			include/UI.h
)

target_sources(GBEmulatorCore
	PRIVATE
		../tracy/public/TracyClient.cpp
	PUBLIC
		FILE_SET tracy
		TYPE HEADERS
		BASE_DIRS
			../tracy/public/tracy
		FILES
			../tracy/public/tracy/Tracy.hpp
)
target_include_directories(GBEmulatorCore PUBLIC include)
target_link_libraries(GBEmulatorCore PUBLIC SDL3::SDL3)
target_link_libraries(GBEmulatorCore PUBLIC SDL3_ttf::SDL3_ttf)