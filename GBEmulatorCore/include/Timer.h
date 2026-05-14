#pragma once

#include <Common.h>

enum class ClockType
{
    CLOCK_00 = 0,
    CLOCK_01 = 1,
    CLOCK_10 = 2,
    CLOCK_11 = 3
};

class Context;
class CORE_API Timer
{
private:
    Context &ctx;

public:
    Timer(Context &ctx);
    ~Timer();

    const static u16 DIV = 0xFF04;
    const static u16 TIMA = 0xFF05;
    const static u16 TMA = 0xFF06;
    const static u16 TAC = 0xFF07;

    int divSubDivision = 0;
    int timaSubDivision = 0;
    int timaFrequency = 0;

    void tick();

    void init();

    u8 getTAC();

    u8 getTIMA();
    void setTIMA(u8 tima);
    void setTIMAFrequency();

    u8 getTMA();
};