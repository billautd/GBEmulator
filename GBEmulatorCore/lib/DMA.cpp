#include <DMA.h>
#include <Context.h>

#define DMA_DEBUG false

DMA::DMA(Context &ctx) : ctx(ctx)
{
}

DMA::~DMA()
{
}

void DMA::start()
{
    source = ctx.mem().readMem(0xFF46);
    currentByte = 0;
    running = true;
    startDelay = 2;
#if DMA_DEBUG
    std::cout << "DMA_START at source byte " << Common::toHexStr(source) << std::endl;
#endif
}

void DMA::tick()
{
    if (!isRunning())
        return;
    // Force tick every 4 T-Cycles
    if (tickDelay > 0)
    {
        tickDelay--;
        return;
    }
    // Once every M-Cycle, not T-Cycle
    tickDelay = 3;
    // Force start procedure after 2 M-cycles
    if (startDelay > 0)
    {
        startDelay--;
        return;
    }
    u16 currentSrcAddress = (source << 8) | currentByte;
    u16 currentDestAddress = 0xFE00 | currentByte;
    ctx.mem().writeMem(currentDestAddress, ctx.mem().readMem(currentSrcAddress));
    currentByte++;
    running = currentByte <= 0x9F;
}