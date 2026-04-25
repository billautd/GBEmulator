#pragma once

#include <Common.h>

class Context;
class CORE_API PPU
{
private:
    Context &ctx;

public:
    PPU(Context &ctx);
    ~PPU();

    void run();
};