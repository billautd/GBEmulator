#include <PPU.h>
#include <Context.h>

PPU::PPU(Context &ctx) : ctx(ctx)
{
}

PPU::~PPU()
{
}

void PPU::run()
{
    std::cout << ctx.mem().at(0x8000) << ctx.mem().at(0x8001) << ctx.mem().at(0x8002) << ctx.mem().at(0x8003) << std::endl;
}