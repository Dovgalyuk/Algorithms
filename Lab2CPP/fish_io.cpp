#include "fish.h"

void fish_output_char(Fish &f)
{
    Data value = pop(f);
    cout << (char)value;
}

void fish_output_num(Fish &f)
{
    Data value = pop(f);
    cout << value;
}

void fish_input(Fish &f)
{
    push(f, f.input.get());
}
