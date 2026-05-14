#pragma once

#include <Common.h>

class Context;
class CORE_API DMA
{
private:
    Context &ctx;

    bool running = false;

public:
    const static u16 DMA_ADDR = 0xFF46;
    DMA(Context &ctx);
    ~DMA();

    u8 source;
    u8 currentByte;
    int tickDelay = 0;
    int startDelay = 0;

    void start();
    void tick();

    bool isRunning() { return running; }
};