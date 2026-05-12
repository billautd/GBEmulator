#include <Joypad.h>
#include <Context.h>

Joypad::Joypad(Context &ctx) : ctx(ctx)
{
}

Joypad::~Joypad()
{
}

void Joypad::tick()
{
    // TODO
    write(JOYPAD, 0b11001111);
}

void Joypad::write(u16 address, u8 value)
{
    ctx.mem().simpleWrite(address, value);
}

u8 &Joypad::read(u16 address)
{
    return ctx.mem().simpleRead(address);
}