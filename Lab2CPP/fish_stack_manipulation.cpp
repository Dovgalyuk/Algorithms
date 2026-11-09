#include "fish.h"

void fish_duplicate(Fish &f)
{
    Data a = pop(f);
    push(f, a);
    push(f, a);
}

void fish_remove(Fish &f)
{
    pop(f);
}

void fish_swap_two(Fish &f)
{
    Data a = pop(f);
    Data b = pop(f);
    push(f, a);
    push(f, b);
}

void fish_swap_three(Fish &f)
{
    Data a = pop(f);
    Data b = pop(f);
    Data c = pop(f);
    push(f, a);
    push(f, c);
    push(f, b);
}

void fish_shift_right(Fish &f)
{
    vector<Data> v = stack_to_vector(f);
    int n = v.size();
    if (n > 0)
    {
        Data first = v[0];
        for (int i = 0; i < n - 1; ++i)
        {
            v[i] = v[i + 1];
        }
        v[n - 1] = first;
    }
    vector_to_stack(f, v);
}

void fish_shift_left(Fish &f)
{
    vector<Data> v = stack_to_vector(f);
    int n = v.size();
    if (n > 0)
    {
        Data last = v[n - 1];
        for (int i = n - 1; i > 0; --i)
        {
            v[i] = v[i - 1];
        }
        v[0] = last;
    }
    vector_to_stack(f, v);
}

void fish_reverse(Fish &f)
{
    vector<Data> v = stack_to_vector(f);
    int n = v.size();
    for (int i = 0; i < n / 2; ++i)
    {
        Data tmp = v[i];
        v[i] = v[n - 1 - i];
        v[n - 1 - i] = tmp;
    }
    vector_to_stack(f, v);
}

void fish_length(Fish &f)
{
    vector<Data> v = stack_to_vector(f);
    vector_to_stack(f, v);
    push(f, v.size());
}

void fish_stack_create(Fish &f)
{
    int n = pop(f);
    vector<Data> v;
    for (int i = 0; i < n; ++i)
    {
        v.push_back(pop(f));
    }
    f.stacks.push_back(stack_create());
    vector_to_stack(f, v);
}

void fish_stack_remove(Fish &f)
{
    if (f.stacks.size() > 1)
    {
        vector<Data> v = stack_to_vector(f);
        stack_delete(f.stacks.back());
        f.stacks.pop_back();
        vector_to_stack(f, v);
    }
}
