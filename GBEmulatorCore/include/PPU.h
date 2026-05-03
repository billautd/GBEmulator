#pragma once

#include <Common.h>

const static u32 colors[4] = {0xFFFFFFFF, 0xAAAAAAFF, 0x555555FF, 0x00000000};
enum PPUModes
{
    HBLANK = 0,
    VBLANK = 1,
    OAM_SCAN = 2,
    DRAWING_PIXELS = 3
};

enum LCDStatuses
{
    LYC_EQ_LY = 2,
    MODE_0 = 3,
    MODE_1 = 4,
    MODE_2 = 5,
    LYC_INT = 5
};

struct Sprite
{
    u8 x;
    u8 y;
    u8 tileIndex;
    u8 flags;
};

class Context;
class CORE_API PPU
{
private:
    Context &ctx;

    u64 cycles;
    u64 frame;
    u16 lineTicks;

    Sprite *oamScanResult = new Sprite[40];

public:
    PPU(Context &ctx);
    ~PPU();

    const static u16 TICKS_PER_LINE = 456;
    const static u16 LINES_PER_FRAME = 153;

    const static u16 LCDC_ADDR = 0xFF40;
    const static u16 STAT_ADDR = 0xFF41;
    const static u16 LY_ADDR = 0xFF44;
    const static u16 LYC_ADDR = 0xFF45;

    void init();
    void tick();

    u64 getFrame() { return frame; };

    void createTile(int x, int y, int tileIndex, SDL_Surface *surface);

    u8 getLY();
    void setLY(u8 ly);
    void incrementLY();

    u8 getLYC();

    void setLCDStatus(LCDStatuses status, bool active);

    // Mode 0 : Horizontal blank
    // Mode 1 : Vertical blank
    // Mode 2 : OAM scan
    // Mode 3 : Drawing pixels -> VRAM is read only
    u8 getMode();
    void setMode(u8 mode);

    void dmaScan();

    void hblank();
    void vblank();
    void oamScan();
    void drawPixels();
};