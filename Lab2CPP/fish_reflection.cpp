#include "fish.h"

void fish_register(Fish &f)
{
    if (f.have_reg)
    {
        push(f, f.reg);
        f.have_reg = false;
    }
    else
    {
        f.reg = pop(f);
        f.have_reg = true;
    }
}

void fish_cell_get(Fish &f)
{
    int gy = pop(f);
    int gx = pop(f);
    if (inside(f, gx, gy))
    {
        push(f, (unsigned char)f.grid[gy][gx]);
    }
    else
    {
        push(f, 0);
    }
}

void fish_cell_put(Fish &f)
{
    int py = pop(f);
    int px = pop(f);
    Data value = pop(f);
    if (!inside(f, px, py))
    {
        error();
    }
    f.grid[py][px] = value;
}
