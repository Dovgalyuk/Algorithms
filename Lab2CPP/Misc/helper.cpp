#include "../fish.h"

void error()
{
    cout << "something smells fishy..." << endl;
    exit(1);
}

void push(Fish &f, Data value)
{
    stack_push(f.stacks.back(), value);
}

Data pop(Fish &f)
{
    if (stack_empty(f.stacks.back()))
    {
        error();
    }
    Data value = stack_get(f.stacks.back());
    stack_pop(f.stacks.back());
    return value;
}

bool inside(Fish &f, int px, int py)
{
    return px >= 0 && px < f.w && py >= 0 && py < f.h;
}

void move(Fish &f)
{
    f.x = f.x + f.dx;
    f.y = f.y + f.dy;
    if (f.x < 0)
    {
        f.x = f.w - 1;
    }
    if (f.x >= f.w)
    {
        f.x = 0;
    }
    if (f.y < 0)
    {
        f.y = f.h - 1;
    }
    if (f.y >= f.h)
    {
        f.y = 0;
    }
}

vector<Data> stack_to_vector(Fish &f)
{
    vector<Data> v;
    while (!stack_empty(f.stacks.back()))
    {
        v.push_back(pop(f));
    }
    return v;
}

void vector_to_stack(Fish &f, vector<Data> &v)
{
    for (int i = (int)v.size() - 1; i >= 0; --i)
    {
        push(f, v[i]);
    }
}
