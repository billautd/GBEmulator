#pragma once

#include <Common.h>
#include <queue>

const static u32 colors[4] = {0xFFFFFFFF, 0xAAAAAAFF, 0x555555FF, 0x00000000};
enum class PPUModes
{
    HBLANK = 0,
    VBLANK = 1,
    OAM_SCAN = 2,
    DRAWING_PIXELS = 3
};

enum class LCDStatuses
{
    MODE_0 = 3,
    MODE_1 = 4,
    MODE_2 = 5,
    LYC_INT = 6
};

enum class LCDControls
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

enum class FIFOFetcherState
{
    TILE,
    TILE_LOW,
    TILE_HIGH,
    SLEEP,
    PUSH
};

struct Pixel
{
    int x;
    int y;
    int colorIndex;
};

class Context;
class CORE_API PPU
{
private:
    Context &ctx;

    u64 cycles;
    u64 frame;
    u16 lineTicks;

    // FIFO
    std::queue<Pixel> fifo = {};
    FIFOFetcherState currentFIFOFetcherState;
    int currentFIFOX;
    int currentFIFOTileY;
    u16 currentFIFOTileMapX;
    u16 currentFIFOTileMapY;
    u8 currentFIFOTileLow;
    u8 currentFIFOTileHigh;
    int fifoDelay = 0;
    bool renderReady = false;

public:
    PPU(Context &ctx);
    ~PPU();

    const static u16 TICKS_PER_LINE = 456;
    const static u16 LINES_PER_FRAME = 153;
    const static int OAM_SCAN_TICKS = 80;

    const static int XRES = 166;
    const static int YRES = 143;

    const static u16 LCDC = 0xFF40;
    const static u16 STAT = 0xFF41;
    const static u16 SCY = 0xFF42;
    const static u16 SCX = 0xFF43;
    const static u16 LY = 0xFF44;
    const static u16 LYC = 0xFF45;
    const static u16 BGP = 0xFF47;
    const static u16 OBP0 = 0xFF48;
    const static u16 OBP1 = 0xFF49;
    const static u16 WY = 0xFF4A;
    const static u16 WX = 0xFF4B;

    void init();
    void tick();

    u64 getFrame() { return frame; };

    void drawPixel(const Pixel &pixel, SDL_Surface *surface);

    u8 getSCX();
    u8 getSCY();

    u8 getLY();
    void setLY(u8 ly);
    void incrementLY();

    u8 getLYC();

    u8 getBGP();

    bool getLCDStatus(LCDStatuses status);
    bool getLCDControl(LCDControls control);

    u8 getWX();
    u8 getWY();
    bool isWindowVisible();

    // Mode 0 : Horizontal blank
    // Mode 1 : Vertical blank
    // Mode 2 : OAM scan
    // Mode 3 : Drawing pixels
    PPUModes getMode();
    void setMode(PPUModes mode);

    void dmaScan();

    void hblank();
    void vblank();
    void oamScan();
    void drawPixels();

    u16 getTileMapBase();
    void clearFIFO()
    {
        std::queue<Pixel> empty;
        std::swap(fifo, empty);
    }

    void vram_write(u16 address, u8 value);
    u8 &vram_read(u16 address);
    void oam_write(u16 address, u8 value);
    u8 &oam_read(u16 address);
    void lcd_write(u16 address, u8 value);
    u8 &lcd_read(u16 address);
};