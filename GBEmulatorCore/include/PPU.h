#pragma once

#include <Common.h>

class Context;
class CORE_API PPU
{
private:
    Context &ctx;

    int cycles;
    // Mode 0 : Horizontal blank
    // Mode 1 : Vertical blank
    // Mode 2 : OAM scan
    // Mode 3 : Drawing pixels
    int mode;

public:
    PPU(Context &ctx);
    ~PPU();

    const static u16 LY_ADDR = 0xFF44;

    void init();
    void run();

    u8 getLY();
    void setLY(u8 ly);
};