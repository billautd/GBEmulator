#pragma once

#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif

#include <format>
#include <iostream>
#include <span>
#include <string>
#include <vector>

#include <SDL3/SDL.h>

// Signed
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

// Unsigned
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

class CORE_API Common
{
public:
	static void delay(int ms);
	static std::string toHexStr(u8 data);
	static std::string toHexStr(u16 data);
	static std::string toHexStr(const u8 *data, const size_t size);
	static std::string toHexStr(const std::span<u8> &array);
};