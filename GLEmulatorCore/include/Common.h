#pragma once

#include <array>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <span>
#include <sstream>
#include <string>
#include <vector>

#include "SDL3/SDL.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

class Common {
public:
	static void delay(int ms);
	static std::string toHexStr(u8 data);
	static std::string toHexStr(u16 data);
	static std::string toHexStr(const u8* data, const size_t size);
	static std::string toHexStr(const std::span<u8>& array);
};