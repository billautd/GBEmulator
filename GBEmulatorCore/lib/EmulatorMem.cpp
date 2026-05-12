#include <EmulatorMem.h>
#include <Context.h>
#include <fstream>

EmulatorMem::EmulatorMem(Context &ctx) : ctx(ctx)
{
}

EmulatorMem::~EmulatorMem()
{
}

void EmulatorMem::init()
{
    data.resize(MEM_SIZE);
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

void EmulatorMem::destroy()
{
    logMem();
}

void EmulatorMem::logMem()
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
        logFile << Common::toHexStr(readMem(i)) << "  ";
        if ((i % 16) == 15)
        {
            logFile << std::endl;
        }
    }
}

void EmulatorMem::simpleWrite(u16 address, u8 value)
{
    data[address] = value;
}

u8 &EmulatorMem::simpleRead(u16 address)
{
    return data[address];
}

void EmulatorMem::writeMem(u16 address, u8 value)
{
    if (address >= 0x0000 && address <= 0x7FFF)
        ctx.cartridge().write(address, value);
    else if (address >= 0x8000 && address <= 0x9FFF)
        ctx.ppu().vram_write(address, value);
    else if (address >= 0xA000 && address <= 0xBFFF)
        ctx.cartridge().write(address, value);
    else if (address >= 0xC000 && address <= 0xDFFF)
        simpleWrite(address, value);
    else if (address >= 0xE000 && address <= 0xFDFF)
    {
        // Echo RAM -> Nothing
    }
    else if (address >= 0xFE00 && address <= 0xFE9F)
        ctx.ppu().oam_write(address, value);
    else if (address >= 0xFEA0 && address <= 0xFEFF)
    {
        // Reserved -> Nothing
    }
    else if (address == Joypad::JOYPAD)
        ctx.joypad().write(address, value);
    // Serial
    else if (address == 0xFF01 || address == 0xFF02)
        simpleWrite(address, value);
    else if (address >= 0xFF03 && address <= 0xFF07)
        ctx.timer().write(address, value);
    else if (address == Interrupts::IE)
        ctx.cpu().getInterrupts().write(address, value);
    // Audio
    else if (address >= 0xFF10 && address <= 0xFF26)
        simpleWrite(address, value);
    // Audiose
    else if (address >= 0xFF30 && address <= 0xFF3F)
        simpleWrite(address, value);
    else if (address == DMA::DMA_ADDR)
        ctx.dma().write(address, value);
    else if (address >= 0xFF40 && address <= 0xFF4B)
        ctx.ppu().lcd_write(address, value);
    // HRAM
    else if (address >= 0xFF80 && address <= 0xFFFE)
        simpleWrite(address, value);
    else if (address == Interrupts::IF)
        ctx.cpu().getInterrupts().write(address, value);
    else
    {
        // std::cerr << "Unrecognized write at address " << Common::toHexStr(address) << std::endl;
        simpleWrite(address, value);
    }
}

u8 EmulatorMem::readMem(u16 address)
{
    if (address >= 0x0000 && address <= 0x7FFF)
        return ctx.cartridge().read(address);
    else if (address >= 0x8000 && address <= 0x9FFF)
        return ctx.ppu().vram_read(address);
    else if (address >= 0xA000 && address <= 0xBFFF)
        return ctx.cartridge().read(address);
    else if (address >= 0xC000 && address <= 0xDFFF)
        return simpleRead(address);
    else if (address >= 0xE000 && address <= 0xFDFF)
    {
        // Echo RAM -> Nothing
        return simpleRead(address);
    }
    else if (address >= 0xFE00 && address <= 0xFE9F)
        return ctx.ppu().oam_read(address);
    else if (address >= 0xFE00 && address <= 0xFEFF)
    {
        // Reserved -> Nothing
        return simpleRead(address);
    }
    else if (address == 0xFF00)
        return ctx.joypad().read(address);
    // Serial
    else if (address == 0xFF01 || address == 0xFF02)
        return simpleRead(address);
    else if (address >= 0xFF04 && address <= 0xFF07)
        return ctx.timer().read(address);
    else if (address == Interrupts::IE)
        return ctx.cpu().getInterrupts().read(address);
    // Audio
    else if (address >= 0xFF10 && address <= 0xFF26)
        return simpleRead(address);
    // Audio
    else if (address >= 0xFF30 && address <= 0xFF3F)
        return simpleRead(address);
    else if (address == DMA::DMA_ADDR)
        return ctx.dma().read(address);
    else if (address >= 0xFF40 && address <= 0xFF4B)
        return ctx.ppu().lcd_read(address);
    // HRAM
    else if (address >= 0xFF80 && address <= 0xFFFE)
        return simpleRead(address);
    else if (address == Interrupts::IF)
        return ctx.cpu().getInterrupts().read(address);
    else
    {
        // std::cerr << "Unrecognized read at address " << Common::toHexStr(address) << std::endl;
        // return simpleRead(address);
        return 0;
    }
}