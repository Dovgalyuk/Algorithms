#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include "stack.h"

bool is_passable(const std::vector<std::string> &grid, int nx, int ny, int move_dir)
{
    if (ny < 0 || ny >= static_cast<int>(grid.size()))
    {
        return false;
    }
    if (nx < 0 || nx >= static_cast<int>(grid[ny].size()))
    {
        return false;
    }

    char ch = grid[ny][nx];
    if (ch == ' ')
    {
        return false;
    }

    if (ch == '^' && move_dir == 2)
    {
        return false;
    }
    if (ch == '>' && move_dir == 3)
    {
        return false;
    }
    if (ch == '<' && move_dir == 1)
    {
        return false;
    }
    if (ch == 'v' && move_dir == 0)
    {
        return false;
    }

    return true;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 1;
    }

    std::ifstream script_file(argv[1]);
    if (!script_file.is_open())
    {
        return 1;
    }

    std::vector<std::string> grid;
    std::string line;
    while (std::getline(script_file, line))
    {
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n'))
        {
            line.pop_back();
        }
        grid.push_back(line);
    }
    script_file.close();

    std::string input_data;
    if (argc >= 3)
    {
        std::ifstream input_file(argv[2]);
        if (input_file.is_open())
        {
            char ch;
            while (input_file.get(ch))
            {
                input_data.push_back(ch);
            }
            input_file.close();
        }
    }

    int start_x = -1;
    int start_y = -1;
    for (int y = 0; y < static_cast<int>(grid.size()); ++y)
    {
        for (int x = 0; x < static_cast<int>(grid[y].size()); ++x)
        {
            if (grid[y][x] == 'S')
            {
                start_x = x;
                start_y = y;
                break;
            }
        }
        if (start_x != -1)
        {
            break;
        }
    }

    if (start_x == -1)
    {
        return 1;
    }

    int x = start_x;
    int y = start_y;
    int dir = 0;

    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {-1, 0, 1, 0};

    uint8_t reg_a = 0;
    uint8_t reg_b = 0;
    Stack *stack = stack_create();

    int steps_since_food = 0;
    int last_food_dist = -1;

    size_t input_pos = 0;

    while (true)
    {
        char current_ch = grid[y][x];

        if (current_ch == 'C')
        {
            break;
        }

        if (current_ch == 'c')
        {
            int dist = steps_since_food;
            if (last_food_dist != -1 && last_food_dist < 4 && dist < 4)
            {
                break;
            }
            last_food_dist = dist;
            steps_since_food = 0;
        }
        else if (current_ch == 'a')
        {
            reg_a = static_cast<uint8_t>(reg_a + 1);
        }
        else if (current_ch == 'b')
        {
            reg_b = static_cast<uint8_t>(reg_b + 1);
        }
        else if (current_ch == 'A')
        {
            reg_a = static_cast<uint8_t>(reg_a - 1);
        }
        else if (current_ch == 'B')
        {
            reg_b = static_cast<uint8_t>(reg_b - 1);
        }
        else if (current_ch == 'z')
        {
            reg_a = 0;
        }
        else if (current_ch == 'Z')
        {
            reg_b = 0;
        }
        else if (current_ch == 'P')
        {
            stack_push(stack, reg_a);
        }
        else if (current_ch == 'p')
        {
            if (!stack_empty(stack))
            {
                int val = stack_get(stack);
                stack_pop(stack);
                std::cout << val;
            }
        }
        else if (current_ch == 'r')
        {
            if (!stack_empty(stack))
            {
                char val = static_cast<char>(stack_get(stack));
                stack_pop(stack);
                std::cout << val;
            }
        }
        else if (current_ch == 'R')
        {
            while (!stack_empty(stack))
            {
                char val = static_cast<char>(stack_get(stack));
                stack_pop(stack);
                std::cout << val;
            }
        }
        else if (current_ch == 'o')
        {
            if (!stack_empty(stack))
            {
                reg_a = static_cast<uint8_t>(stack_get(stack));
                stack_pop(stack);
            }
        }
        else if (current_ch == 'O')
        {
            if (!stack_empty(stack))
            {
                reg_b = static_cast<uint8_t>(stack_get(stack));
                stack_pop(stack);
            }
        }
        else if (current_ch == 'd')
        {
            if (!stack_empty(stack))
            {
                stack_pop(stack);
            }
        }
        else if (current_ch == 'i')
        {
            while (input_pos < input_data.size())
            {
                stack_push(stack, static_cast<uint8_t>(input_data[input_pos]));
                ++input_pos;
            }
        }

        if (steps_since_food >= 10 && current_ch != 'c' && current_ch != 'C')
        {
            break;
        }

        int candidates[4] = {
            (dir + 3) % 4,
            dir,
            (dir + 1) % 4,
            (dir + 2) % 4
        };

        bool found = false;
        int next_dir = dir;
        int next_x = x;
        int next_y = y;

        for (int i = 0; i < 4; ++i)
        {
            int cand_dir = candidates[i];
            if (i == 0)
            {
                if (current_ch == 'T' && reg_b != 0)
                {
                    continue;
                }
                if (current_ch == 'Y' && reg_a != reg_b)
                {
                    continue;
                }
            }

            int target_x = x + dx[cand_dir];
            int target_y = y + dy[cand_dir];

            if (is_passable(grid, target_x, target_y, cand_dir))
            {
                found = true;
                next_dir = cand_dir;
                next_x = target_x;
                next_y = target_y;
                break;
            }
        }

        if (!found)
        {
            break;
        }

        x = next_x;
        y = next_y;
        dir = next_dir;
        ++steps_since_food;
    }

    stack_delete(stack);
    return 0;
}
