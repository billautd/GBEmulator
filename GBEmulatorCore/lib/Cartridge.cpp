#include <Cartridge.h>
#include <Context.h>
#include <fstream>

const std::string logoDump = "CE ED 66 66 CC 0D 00 0B 03 73 00 83 00 0C 00 0D 00 08 11 1F 88 89 00 0E DC CC 6E E6 DD DD D9 99 BB BB 67 63 6E 0E EC CC DD DC 99 9F BB B9 33 3E";

Cartridge::Cartridge(Context &ctx) : ctx(ctx)
{
}

Cartridge::~Cartridge()
{
}

void Cartridge::readBytesFromRomData(size_t offset, const std::span<u8> &array)
{
	for (int i = 0; i < array.size(); i++)
	{
		array[i] = ctx.mem().readMem(i + offset);
	}
}

bool Cartridge::checkHeaderChecksum()
{
	u8 checksum = 0;
	for (u16 address = 0x0134; address <= 0x14C; address++)
	{
		checksum = checksum - ctx.mem().readMem(address) - 1;
	}
	return checksum == headerChecksum.at(0);
}

bool Cartridge::checkGlobalChecksum()
{
	u16 checksum = 0;
	for (size_t i = 0; i < actualRomSize; i++)
	{
		// Ignore checksum itself
		if (i == 0x14E || i == 0x14F)
		{
			continue;
		}
		checksum += ctx.mem().readMem(i);
	}
	// Big endian
	return checksum == (globalChecksum.at(1) + 256 * globalChecksum.at(0));
}

void Cartridge::init(const char *path)
{
	std::cout << std::format("Loading cartridge from path: {}\n", path);

	std::ifstream file(path, std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << std::format("Failed to open cartridge file at {}\n", path);
		return;
	}

	// Read full ROM data
	file.seekg(0, file.end);
	actualRomSize = file.tellg();
	file.seekg(0);
	char ch;
	int i = 0;
	while (file.get(ch))
	{
		ctx.mem().writeMem(i, (u8)ch);
		i++;
	}

	// Read header from ROM data
	readBytesFromRomData(0x100, entryPoint);
	readBytesFromRomData(0x104, logo);
	readBytesFromRomData(0x134, title);
	readBytesFromRomData(0x144, newLicenseCode);
	readBytesFromRomData(0x146, sgbFlag);
	readBytesFromRomData(0x147, cartridgeType);
	readBytesFromRomData(0x148, romSize);
	readBytesFromRomData(0x149, ramSize);
	readBytesFromRomData(0x14A, destinationCode);
	readBytesFromRomData(0x14B, oldLicenseeCode);
	readBytesFromRomData(0x14C, maskRomVersionNumber);
	readBytesFromRomData(0x14D, headerChecksum);
	readBytesFromRomData(0x14E, globalChecksum);

	std::cout << "Loaded cartridge" << std::endl;
	std::cout << "Entry point : " << Common::toHexStr(entryPoint) << std::endl;
	std::cout << "Logo : " << Common::toHexStr(logo) << std::endl;
	std::cout << "Title : " << Common::toHexStr(title) << std::endl;
	std::cout << "New license code : " << Common::toHexStr(newLicenseCode) << std::endl;
	std::cout << "SGB flag : " << Common::toHexStr(sgbFlag) << std::endl;
	std::cout << "Cartridge type : " << Common::toHexStr(cartridgeType) << std::endl;
	std::cout << "ROM size : " << Common::toHexStr(romSize) << std::endl;
	std::cout << "RAM size : " << Common::toHexStr(ramSize) << std::endl;
	std::cout << "Destination code : " << Common::toHexStr(destinationCode) << std::endl;
	std::cout << "Old licensee code : " << Common::toHexStr(oldLicenseeCode) << std::endl;
	std::cout << "Mask ROM version number : " << Common::toHexStr(maskRomVersionNumber) << std::endl;
	std::cout << "Header checksum : " << Common::toHexStr(headerChecksum) << std::endl;
	std::cout << "Global checksum : " << Common::toHexStr(globalChecksum) << std::endl;

	if (!checkHeaderChecksum())
	{
		std::cerr << "Wrong header checksum" << std::endl;
	}
	if (!checkGlobalChecksum())
	{
		std::cerr << "Wrong global checksum" << std::endl;
	}
	std::cout << std::endl;
}

void Cartridge::write(u16 address, u8 value)
{
	ctx.mem().simpleWrite(address, value);
}

u8 &Cartridge::read(u16 address)
{
	return ctx.mem().simpleRead(address);
}