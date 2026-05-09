#pragma once

#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif

#include <format>
#include <iostream>
#include <memory>
#include <span>
#include <string>
#include <math.h>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <Tracy.hpp>

// Signed
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// Unsigned
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

class CORE_API Common
{
public:
	static u64 getTicks();
	static void delay(int ns);
	static std::string toHexStr(u8 data);
	static std::string toHexStr(u16 data);
	static std::string toHexStr(u64 data);
	static std::string toHexStr(const u8 *data, const size_t size);
	static std::string toHexStr(const std::span<u8> &array);

	static bool getBit(u8 value, int index);
	static u8 setBit(u8 value, int index);
	static u8 resetBit(u8 value, int index);
};