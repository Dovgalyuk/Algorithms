#ifndef FISH_H
#define FISH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "stack.h"

using namespace std;

struct Fish
{
    vector<string> grid;
    vector<Stack*> stacks;
    int x = 0;
    int y = 0;
    int dx = 1;
    int dy = 0;
    int w = 0;
    int h = 0;
    char q = 0;
    bool have_reg = false;
    Data reg = 0;
    ifstream input;
};

void error();
void push(Fish &f, Data value);
Data pop(Fish &f);
bool inside(Fish &f, int px, int py);
void move(Fish &f);
vector<Data> stack_to_vector(Fish &f);
void vector_to_stack(Fish &f, vector<Data> &v);

void fish_right(Fish &f);
void fish_left(Fish &f);
void fish_up(Fish &f);
void fish_down(Fish &f);
void fish_mirror_slash(Fish &f);
void fish_mirror_backslash(Fish &f);
void fish_mirror_vertical(Fish &f);
void fish_mirror_horizontal(Fish &f);
void fish_mirror_both(Fish &f);
void fish_random_direction(Fish &f);
void fish_trampoline(Fish &f);
void fish_trampoline_conditional(Fish &f);
void fish_jump(Fish &f);

void fish_add(Fish &f);
void fish_sub(Fish &f);
void fish_mul(Fish &f);
void fish_div(Fish &f);
void fish_mod(Fish &f);

void fish_equal(Fish &f);
void fish_greater(Fish &f);
void fish_less(Fish &f);

void fish_duplicate(Fish &f);
void fish_remove(Fish &f);
void fish_swap_two(Fish &f);
void fish_swap_three(Fish &f);
void fish_shift_right(Fish &f);
void fish_shift_left(Fish &f);
void fish_reverse(Fish &f);
void fish_length(Fish &f);
void fish_stack_create(Fish &f);
void fish_stack_remove(Fish &f);

void fish_output_char(Fish &f);
void fish_output_num(Fish &f);
void fish_input(Fish &f);

void fish_register(Fish &f);
void fish_cell_get(Fish &f);
void fish_cell_put(Fish &f);

void interpretation(Fish &f, char c);
void read_script(Fish &f, const string &path);
void run(Fish &f);

#endif
