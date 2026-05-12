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
    MODE_0 = 3,
    MODE_1 = 4,
    MODE_2 = 5,
    LYC_INT = 5
};

enum LCDControls
{
    BG_WINDOW = 0,
    OBJ_ENABLE = 1,
    OBJ_SIZE = 2,
    BG_TILE_MAP = 3,
    BG_WINDOW_TILES = 4,
    WINDOW_ENABLE = 5,
    WINDOW_TILE_MAP = 6,
    LCD_PPU_ENABLE = 7
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

    std::vector<Sprite> oamScanResult = {};

public:
    PPU(Context &ctx);
    ~PPU();

    const static u16 TICKS_PER_LINE = 456;
    const static u16 LINES_PER_FRAME = 153;

    const static u16 LCDC = 0xFF40;
    const static u16 STAT = 0xFF41;
    const static u16 LY = 0xFF44;
    const static u16 LYC = 0xFF45;
    const static u16 WY = 0xFF4A;
    const static u16 WX = 0xFF4B;

    void init();
    void tick();

    u64 getFrame() { return frame; };

    void createPixel(int x, int y, u8 color, SDL_Surface *surface);

    u8 getLY();
    void setLY(u8 ly);
    void incrementLY();

    u8 getLYC();

    bool getLCDStatus(LCDStatuses status);
    bool getLCDControl(LCDControls control);

    u8 getWX();
    u8 getWY();

    // Mode 0 : Horizontal blank
    // Mode 1 : Vertical blank
    // Mode 2 : OAM scan
    // Mode 3 : Drawing pixels
    u8 getMode();
    void setMode(u8 mode);

    void dmaScan();

    void hblank();
    void vblank();
    void oamScan();
    void drawPixels();

    void vram_write(u16 address, u8 value);
    u8 &vram_read(u16 address);
    void oam_write(u16 address, u8 value);
    u8 &oam_read(u16 address);
    void lcd_write(u16 address, u8 value);
    u8 &lcd_read(u16 address);
};