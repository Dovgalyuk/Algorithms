#include "fish.h"

void fish_right(Fish &f)
{
    f.dx = 1;
    f.dy = 0;
}

void fish_left(Fish &f)
{
    f.dx = -1;
    f.dy = 0;
}

void fish_up(Fish &f)
{
    f.dx = 0;
    f.dy = -1;
}

void fish_down(Fish &f)
{
    f.dx = 0;
    f.dy = 1;
}

void fish_mirror_slash(Fish &f)
{
    int old_dx = f.dx;
    f.dx = -f.dy;
    f.dy = -old_dx;
}

void fish_mirror_backslash(Fish &f)
{
    int old_dx = f.dx;
    f.dx = f.dy;
    f.dy = old_dx;
}

void fish_mirror_vertical(Fish &f)
{
    f.dx = -f.dx;
}

void fish_mirror_horizontal(Fish &f)
{
    f.dy = -f.dy;
}

void fish_mirror_both(Fish &f)
{
    f.dx = -f.dx;
    f.dy = -f.dy;
}

void fish_random_direction(Fish &f)
{
    int r = rand() % 4;
    if (r == 0)
    {
        fish_right(f);
    }
    if (r == 1)
    {
        fish_left(f);
    }
    if (r == 2)
    {
        fish_down(f);
    }
    if (r == 3)
    {
        fish_up(f);
    }
}

void fish_trampoline(Fish &f)
{
    move(f);
}

void fish_trampoline_conditional(Fish &f)
{
    Data value = pop(f);
    if (value == 0)
    {
        move(f);
    }
}

void fish_jump(Fish &f)
{
    int new_y = pop(f);
    int new_x = pop(f);
    f.x = new_x % f.w;
    f.y = new_y % f.h;
    if (f.x < 0) f.x += f.w;
    if (f.y < 0) f.y += f.h;
}
