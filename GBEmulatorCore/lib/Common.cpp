#include <Common.h>
#include <sstream>
#include <iomanip>

void Common::delay(int ms)
{
	SDL_Delay(ms);
}

std::string Common::toHexStr(u8 data)
{
	std::ostringstream oss;
	oss << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << static_cast<int>(data);
	return oss.str();
}

std::string Common::toHexStr(u16 data)
{
	std::ostringstream oss;
	oss << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << static_cast<int>(data);
	return oss.str();
}

std::string Common::toHexStr(const u8 *data, const size_t size)
{
	std::ostringstream oss;
	for (std::size_t i = 0; i < size; i++)
	{
		oss << toHexStr(data[i]) << " ";
	}
	return oss.str();
}

std::string Common::toHexStr(const std::span<u8> &array)
{
	std::ostringstream oss;
	for (u8 b : array)
	{
		oss << toHexStr(b) << " ";
	}
	return oss.str();
}
