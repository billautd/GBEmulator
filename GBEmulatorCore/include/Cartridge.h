#pragma once

#include <Common.h>

class Context;
class CORE_API Cartridge
{
private:
	Context &ctx;

	// 0x0100 -> 0x0103
	std::array<u8, 0x04> entryPoint = {};
	// 0x0104 -> 0x0133
	std::array<u8, 0x30> logo = {};
	// 0x0134 -> 0x0143
	std::array<u8, 0x10> title = {};
	// 0x0144 -> 0x0145
	std::array<u8, 0x02> newLicenseCode = {};
	// 0x0146
	std::array<u8, 0x01> sgbFlag = {};
	// 0x0147
	std::array<u8, 0x01> cartridgeType = {};
	// 0x0148
	std::array<u8, 0x01> romSize = {};
	// 0x0149
	std::array<u8, 0x01> ramSize = {};
	// 0x014A
	std::array<u8, 0x01> destinationCode = {};
	// 0x014B
	std::array<u8, 0x01> oldLicenseeCode = {};
	// 0x014C
	std::array<u8, 0x01> maskRomVersionNumber = {};
	// 0x014D
	std::array<u8, 0x01> headerChecksum = {};
	// 0x014E -> 0x014F
	std::array<u8, 0x02> globalChecksum = {};

	// Bytes
	std::size_t actualRomSize;

	void readBytesFromRomData(std::size_t offset, const std::span<u8> &array);
	bool checkHeaderChecksum();
	bool checkGlobalChecksum();

public:
	Cartridge(Context &ctx);
	~Cartridge();

	void loadCartrige(const char *path);
};
