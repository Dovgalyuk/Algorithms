#include "fish.h"

void fish_add(Fish &f)
{
    Data b = pop(f);
    Data a = pop(f);
    push(f, a + b);
}

void fish_sub(Fish &f)
{
    Data b = pop(f);
    Data a = pop(f);
    push(f, a - b);
}

void fish_mul(Fish &f)
{
    Data b = pop(f);
    Data a = pop(f);
    push(f, a * b);
}

void fish_div(Fish &f)
{
    Data b = pop(f);
    Data a = pop(f);
    if (b == 0)
    {
        error();
    }
    push(f, a / b);
}

void fish_mod(Fish &f)
{
    Data b = pop(f);
    Data a = pop(f);
    if (b == 0)
    {
        error();
    }
    push(f, a % b);
}
