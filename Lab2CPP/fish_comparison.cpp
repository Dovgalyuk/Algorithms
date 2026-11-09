#include "fish.h"

void fish_equal(Fish &f)
{
    Data b = pop(f);
    Data a = pop(f);
    push(f, a == b);
}

void fish_greater(Fish &f)
{
    Data b = pop(f);
    Data a = pop(f);
    push(f, a > b);
}

void fish_less(Fish &f)
{
    Data b = pop(f);
    Data a = pop(f);
    push(f, a < b);
}
