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
    ctx.mem().writeMem(JOYPAD, 0b11001111);
}