#pragma once

#include <Common.h>

class Context;
class CORE_API Joypad
{
private:
    Context &ctx;

public:
    const static u16 JOYPAD = 0xFF00;
    Joypad(Context &ctx);
    ~Joypad();

    void tick();

    void write(u16 address, u8 value);
    u8 &read(u16 address);
};