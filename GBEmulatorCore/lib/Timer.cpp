#include <Timer.h>
#include <Context.h>

Timer::Timer(Context &ctx) : ctx(ctx)
{
}

Timer::~Timer()
{
}

void Timer::init()
{
}

void Timer::tick()
{
    // Update TIMA clock frequency
    setTIMAFrequency();
    divSubDivision++;

    // Check if TIMA increment is enabled
    if (Common::getBit(getTAC(), 2))
        timaSubDivision++;

    // Not using writeMem, because writeMem resets it to 0
    // When div sub division is > 255, increase value at DIV
    if (divSubDivision > 0xFF)
    {
        divSubDivision -= 0xFF;
        ctx.mem().getMem()[DIV]++;
    }
    // When tima sub division reaching clock frequency, increment value at TIMA
    // If TIMA overflow, request interrupt and reset TIMA value to value in TMA
    if (timaSubDivision > timaFrequency)
    {
        timaSubDivision -= timaFrequency;
        u16 newTIMA = getTIMA() + 1;
        if (newTIMA > 0xFF)
        {
            setTIMA(getTMA());
            ctx.cpu().getInterrupts().requestInterrupt(InterruptType::INT_TIMER);
        }
        else
        {
            setTIMA(newTIMA);
        }
    }
}

void Timer::setTIMAFrequency()
{
    u8 tac = getTAC();
    u8 clockType = (Common::getBit(tac, 1) << 1) | Common::getBit(tac, 0);
    switch (clockType)
    {
    case ClockType::CLOCK_00:
        timaFrequency = 256 * 4;
        break;
    case ClockType::CLOCK_01:
        timaFrequency = 4 * 4;
        break;
    case ClockType::CLOCK_10:
        timaFrequency = 16 * 4;
        break;
    case ClockType::CLOCK_11:
        timaFrequency = 64 * 4;
        break;
    default:
        std::cerr << "Incorrect clock type " << clockType << std::endl;
        ctx.setRunning(false);
        break;
    }
}

u8 Timer::getTAC()
{
    return ctx.mem().readMem(TAC);
}

u8 Timer::getTIMA()
{
    return ctx.mem().readMem(TIMA);
}
void Timer::setTIMA(u8 tima)
{
    ctx.mem().writeMem(TIMA, tima);
}

u8 Timer::getTMA()
{
    return ctx.mem().readMem(TMA);
}

void Timer::write(u16 address, u8 value)
{
    // Writing DIV sets it to 0
    if (address == DIV)
        ctx.mem().simpleWrite(address, 0);
    else
        ctx.mem().simpleWrite(address, value);
}

u8 &Timer::read(u16 address)
{
    return ctx.mem().simpleRead(address);
}