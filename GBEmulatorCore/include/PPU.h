#pragma once

#include <Common.h>

const static u32 colors[4] = {0xFFFFFFFF, 0xAAAAAAFF, 0x555555FF, 0x00000000};
enum PPU_MODES
{
    HBLANK,
    VBLANK,
    OAM_SCAN,
    DRAWING_PIXELS
};

class Context;
class CORE_API PPU
{
private:
    Context &ctx;

    u64 cycles;
    u64 frame;
    u16 lineTicks;

public:
    PPU(Context &ctx);
    ~PPU();

    const static u16 TICKS_PER_LINE = 456;
    const static u16 LINES_PER_FRAME = 153;

    const static u16 STAT_ADDR = 0xFF41;
    const static u16 LY_ADDR = 0xFF44;
    const static u16 LYC_ADDR = 0xFF45;

    void init();
    void tick();

    u64 getFrame() { return frame; };

    void createTile(int x, int y, int tileIndex, int scale, SDL_Surface *surface);

    u8 getLY();
    void setLY(u8 ly);
    void incrementLY();

    // Mode 0 : Horizontal blank
    // Mode 1 : Vertical blank
    // Mode 2 : OAM scan
    // Mode 3 : Drawing pixels -> VRAM is read only
    u8 getMode();
    void setMode(u8 mode);

    void hblank();
    void vblank();
    void oamScan();
    void drawPixels();

    bool isVRAMAccessible() { return true; }
};