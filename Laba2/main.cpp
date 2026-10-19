#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "stack.h"
#include <cstdint>

typedef std::vector<std::string> Grid;

struct Rat
{
    int x, y;
    int dir;
    int steps;
    int food_steps;
    int food_count;
};

const int DX[4] = {0, 1, 0, -1};
const int DY[4] = {-1, 0, 1, 0};

bool can_enter(const Grid &grid, int x, int y, int dir)
{
    if (y < 0 || y >= static_cast<int>(grid.size()))
        return false;
    if (x < 0 || x >= static_cast<int>(grid[y].size()))
        return false;

    char c = grid[y][x];
    if (c == ' ')
        return false;
    if (c == '^' && dir == 2)
        return false;
    if (c == '>' && dir == 3)
        return false;
    if (c == '<' && dir == 1)
        return false;
    if (c == 'v' && dir == 0)
        return false;

    return true;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 1;
    }
    std::ifstream mf(argv[1]);
    if (!mf)
    {
        return 1;
    }

    Grid grid;
    std::string line;
    while (std::getline(mf, line))
    {
        grid.push_back(line);
    }
    std::string input_data;
    if (argc >= 3)
    {
        std::ifstream inf(argv[2]);
        if (inf)
        {
            char ch;
            while (inf.get(ch))
            {
                input_data.push_back(ch);
            }
        }
    }

    Rat rat = {0, 0, 0, 0, 0, 0};
    bool found_start = false;
    for (int y = 0; y < static_cast<int>(grid.size()) && !found_start; ++y)
        for (int x = 0; x < static_cast<int>(grid[y].size()); ++x)
            if (grid[y][x] == 'S')
            {
                rat.x = x;
                rat.y = y;
                rat.dir = 0;
                found_start = true;
                break;
            }
    if (!found_start)
    {
        return 1;
    }

    Stack *stack = stack_create();
    uint8_t A = 0, B = 0;
    size_t input_pos = 0;
    bool running = true;

    while (running)
    {
        char c = grid[rat.y][rat.x];

        if (c != 'c' && c != 'C' && rat.steps > 10)
        {
            return 1;
        }

        switch (c)
        {
        case '+':
            break;
        case 'S':
            break;
        case 'c':
            if (rat.food_steps < 4)
                rat.food_count++;
            else
                rat.food_count = 1;
            rat.food_steps = 0;
            rat.steps = 0;
            if (rat.food_count >= 3)
            {
                return 1;
            }
            break;
        case 'C':
            running = false;
            break;
        case 'a':
            A = (A + 1);
            break;
        case 'b':
            B = (B + 1);
            break;
        case 'A':
            A = (A - 1);
            break;
        case 'B':
            B = (B - 1);
            break;
        case 'z':
            A = 0;
            break;
        case 'Z':
            B = 0;
            break;
        case 'P':
            stack_push(stack, A);
            break;
        case 'p':
            if (!stack_empty(stack))
            {
                std::cout << static_cast<int>(stack_get(stack));
                stack_pop(stack);
            }
            break;
        case 'r':
            if (!stack_empty(stack))
            {
                std::cout << static_cast<char>(stack_get(stack));
                stack_pop(stack);
            }
            break;
        case 'R':
            while (!stack_empty(stack))
            {
                std::cout << static_cast<char>(stack_get(stack));
                stack_pop(stack);
            }
            break;
        case 'o':
            if (!stack_empty(stack))
            {
                A = stack_get(stack);
                stack_pop(stack);
            }
            break;
        case 'O':
            if (!stack_empty(stack))
            {
                B = stack_get(stack);
                stack_pop(stack);
            }
            break;
        case 'd':
            if (!stack_empty(stack))
                stack_pop(stack);
            break;
        case 'i':
            if (input_pos < input_data.size())
            {
                stack_push(stack, (unsigned char)input_data[input_pos]);
                input_pos++;
            }
            break;
        default:
            break;
        }
        if (!running)
        {
            break;
        }

        int left_dir = (rat.dir + 3) % 4;
        int straight_dir = rat.dir;
        int right_dir = (rat.dir + 1) % 4;
        int back_dir = (rat.dir + 2) % 4;

        bool block_left = false;
        if (c == 'T' && B != 0)
            block_left = true;
        if (c == 'Y' && A != B)
            block_left = true;

        int nx = rat.x, ny = rat.y, ndir = rat.dir;
        bool moved = false;

        if (!block_left)
        {
            nx = rat.x + DX[left_dir];
            ny = rat.y + DY[left_dir];
            if (can_enter(grid, nx, ny, left_dir))
            {
                ndir = left_dir;
                moved = true;
            }
        }
        if (!moved)
        {
            nx = rat.x + DX[straight_dir];
            ny = rat.y + DY[straight_dir];
            if (can_enter(grid, nx, ny, straight_dir))
            {
                ndir = straight_dir;
                moved = true;
            }
        }
        if (!moved)
        {
            nx = rat.x + DX[right_dir];
            ny = rat.y + DY[right_dir];
            if (can_enter(grid, nx, ny, right_dir))
            {
                ndir = right_dir;
                moved = true;
            }
        }
        if (!moved)
        {
            nx = rat.x + DX[back_dir];
            ny = rat.y + DY[back_dir];
            if (can_enter(grid, nx, ny, back_dir))
            {
                ndir = back_dir;
                moved = true;
            }
        }
        if (!moved)
        {
            return 1;
        }

        rat.x = nx;
        rat.y = ny;
        rat.dir = ndir;
        rat.steps++;
        rat.food_steps++;
    }

    stack_delete(stack);
    return 0;
}