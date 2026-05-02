#include <Mem.h>
#include <Context.h>
#include <fstream>

Mem::Mem(Context &ctx) : ctx(ctx)
{
}

Mem::~Mem()
{
}

void Mem::init()
{
    data = new u8[MEM_SIZE];
    writeMem(0xFF00, 0xCF);
    writeMem(0xFF01, 0x00);
    writeMem(0xFF02, 0x7E);
    writeMem(0xFF04, 0xAB);
    writeMem(0xFF05, 0x00);
    writeMem(0xFF06, 0x00);
    writeMem(0xFF07, 0xF8);
    writeMem(0xFF10, 0x80);
    writeMem(0xFF11, 0xBF);
    writeMem(0xFF12, 0xF3);
    writeMem(0xFF13, 0xFF);
    writeMem(0xFF14, 0xBF);
    writeMem(0xFF16, 0x3F);
    writeMem(0xFF17, 0x00);
    writeMem(0xFF18, 0xFF);
    writeMem(0xFF19, 0xBF);
    writeMem(0xFF1A, 0x7F);
    writeMem(0xFF1B, 0xFF);
    writeMem(0xFF1C, 0x9F);
    writeMem(0xFF1D, 0xFF);
    writeMem(0xFF1E, 0xBF);
    writeMem(0xFF20, 0xFF);
    writeMem(0xFF21, 0x00);
    writeMem(0xFF22, 0x00);
    writeMem(0xFF23, 0xBF);
    writeMem(0xFF24, 0x77);
    writeMem(0xFF25, 0xF3);
    writeMem(0xFF26, 0xF1);
    writeMem(0xFF40, 0x91);
    writeMem(0xFF41, 0x85);
    writeMem(0xFF42, 0x00);
    writeMem(0xFF43, 0x00);
    writeMem(0xFF44, 0x00);
    writeMem(0xFF45, 0x00);
    writeMem(0xFF46, 0xFF);
    writeMem(0xFF47, 0xFC);
    writeMem(0xFF48, 0x00);
    writeMem(0xFF49, 0x00);
    writeMem(0xFF4A, 0x00);
    writeMem(0xFF4B, 0x00);
    writeMem(0xFFFF, 0x00);
}

void Mem::destroy()
{
    logMem();
}

void Mem::logMem()
{
    std::ofstream logFile("memory.txt");
    logFile << ctx.regs().log() << std::endl
            << std::endl;
    logFile << "       0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F" << std::endl;
    for (int i = 0; i < MEM_SIZE; i++)
    {
        if ((i % 16) == 0)
        {
            logFile << Common::toHexStr((u16)((i / 16) << 4)) << "  ";
        }
        logFile << Common::toHexStr(data[i]) << "  ";
        if ((i % 16) == 15)
        {
            logFile << std::endl;
        }
    }
}

void Mem::writeMem(u16 address, u8 value)
{
    data[address] = value;
    if (address == 0xFF46)
        ctx.dma().start();
}

u8 Mem::readMem(u16 address)
{
    return data[address];
}