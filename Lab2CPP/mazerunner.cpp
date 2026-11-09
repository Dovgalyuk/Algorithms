#include <iostream>
#include <fstream>
#include <string>

#include "vector.h"
#include "stack.h"

typedef Vector<std::string> StringVector;
typedef Stack<unsigned char> ByteStack;

const std::string PATH_CHARS = "+ScCabABTPprR><^vzZoOYdi";

const int UP = 0;
const int LEFT = 1;
const int DOWN = 2;
const int RIGHT = 3;

struct Rat
{
    int x;
    int y;
    int direction;
    int hunger;
    int food_cooldown;
};

bool read_lines(std::ifstream& input, StringVector& lines)
{
    std::string line;

    while (std::getline(input, line))
    {
        if (!line.empty() && line[line.size() - 1] == '\r')
        {
            line.erase(line.size() - 1);
        }

        lines.resize(lines.size() + 1);
        lines.set(lines.size() - 1, line);
    }

    return lines.size() > 0;
}

char get_cell(const StringVector& maze, int x, int y)
{
    if (y < 0 || y >= (int)maze.size())
    {
        return ' ';
    }

    std::string line = maze.get(y);
    if (x < 0 || x >= (int)line.size())
    {
        return ' ';
    }

    return line[x];
}

bool can_step(const StringVector& maze, int x, int y, int direction)
{
    if (direction == UP)
    {
        --y;
    }
    else if (direction == LEFT)
    {
        --x;
    }
    else if (direction == DOWN)
    {
        ++y;
    }
    else
    {
        ++x;
    }

    char cell = get_cell(maze, x, y);

    if (PATH_CHARS.find(cell) == std::string::npos)
    {
        return false;
    }

    if (direction == UP && cell == 'v')
    {
        return false;
    }
    if (direction == LEFT && cell == '>')
    {
        return false;
    }
    if (direction == DOWN && cell == '^')
    {
        return false;
    }
    if (direction == RIGHT && cell == '<')
    {
        return false;
    }

    return true;
}

Rat create_rat(const StringVector& maze)
{
    Rat rat;
    rat.x = 0;
    rat.y = 0;
    rat.direction = UP;
    rat.hunger = 0;
    rat.food_cooldown = 0;

    for (size_t y = 0; y < maze.size(); ++y)
    {
        size_t position = maze.get(y).find('S');
        if (position != std::string::npos)
        {
            rat.x = (int)position;
            rat.y = (int)y;
        }
    }

    return rat;
}

bool pop_value(ByteStack& stack, unsigned char& value)
{
    if (stack.empty())
    {
        return false;
    }

    value = stack.get();
    stack.pop();

    return true;
}

void push_line(ByteStack& stack, const std::string& line)
{
    for (int i = (int)line.size() - 1; i >= 0; --i)
    {
        stack.push((unsigned char)line[i]);
    }
}

bool is_left_allowed(char command, unsigned char accumulator_a, unsigned char accumulator_b)
{
    if (command == 'T' && accumulator_b != 0)
    {
        return false;
    }
    if (command == 'Y' && accumulator_a != accumulator_b)
    {
        return false;
    }

    return true;
}

int choose_direction(const StringVector& maze, const Rat& rat, bool left_allowed)
{
    int left = (rat.direction + 1) % 4;
    int forward = rat.direction;
    int right = (rat.direction + 3) % 4;
    int back = (rat.direction + 2) % 4;

    if (left_allowed && can_step(maze, rat.x, rat.y, left))
    {
        return left;
    }
    if (can_step(maze, rat.x, rat.y, forward))
    {
        return forward;
    }
    if (can_step(maze, rat.x, rat.y, right))
    {
        return right;
    }
    if (can_step(maze, rat.x, rat.y, back))
    {
        return back;
    }

    return -1;
}

void move_rat(Rat& rat)
{
    if (rat.direction == UP)
    {
        --rat.y;
    }
    else if (rat.direction == LEFT)
    {
        --rat.x;
    }
    else if (rat.direction == DOWN)
    {
        ++rat.y;
    }
    else
    {
        ++rat.x;
    }
}

void run_maze(const StringVector& maze, const StringVector& input)
{
    ByteStack stack;
    unsigned char accumulator_a = 0;
    unsigned char accumulator_b = 0;
    unsigned char value = 0;
    size_t input_line = 0;

    Rat rat = create_rat(maze);

    while (true)
    {
        char command = get_cell(maze, rat.x, rat.y);

        if (command == 'C')
        {
            break;
        }
        else if (command == 'c')
        {
            rat.hunger = 0;
            ++rat.food_cooldown;
        }
        else if (command == 'a')
        {
            ++accumulator_a;
        }
        else if (command == 'b')
        {
            ++accumulator_b;
        }
        else if (command == 'A')
        {
            --accumulator_a;
        }
        else if (command == 'B')
        {
            --accumulator_b;
        }
        else if (command == 'z')
        {
            accumulator_a = 0;
        }
        else if (command == 'Z')
        {
            accumulator_b = 0;
        }
        else if (command == 'P')
        {
            stack.push(accumulator_a);
        }
        else if (command == 'p')
        {
            if (pop_value(stack, value))
            {
                std::cout << (int)value << std::endl;
            }
        }
        else if (command == 'r')
        {
            if (pop_value(stack, value))
            {
                std::cout << (char)value << std::endl;
            }
        }
        else if (command == 'R')
        {
            while (pop_value(stack, value))
            {
                std::cout << (char)value;
            }
            std::cout << std::endl;
        }
        else if (command == 'o')
        {
            pop_value(stack, accumulator_a);
        }
        else if (command == 'O')
        {
            pop_value(stack, accumulator_b);
        }
        else if (command == 'd')
        {
            pop_value(stack, value);
        }
        else if (command == 'i')
        {
            if (input_line < input.size())
            {
                push_line(stack, input.get(input_line));
                ++input_line;
            }
        }

        if (rat.hunger >= 10)
        {
            std::cerr << "Rat starved at (" << rat.x << ", " << rat.y << ")" << std::endl;
            break;
        }
        if (rat.food_cooldown >= 3)
        {
            std::cerr << "Rat overate at (" << rat.x << ", " << rat.y << ")" << std::endl;
            break;
        }

        ++rat.hunger;
        if (rat.hunger % 5 == 0 && rat.food_cooldown > 0)
        {
            --rat.food_cooldown;
        }

        bool left_allowed = is_left_allowed(command, accumulator_a, accumulator_b);
        int direction = choose_direction(maze, rat, left_allowed);

        if (direction < 0)
        {
            std::cerr << "Rat is stuck at (" << rat.x << ", " << rat.y << ")" << std::endl;
            break;
        }

        rat.direction = direction;
        move_rat(rat);
    }
}

int main(int argc, char** argv)
{
    if (argc <= 2)
    {
        std::cerr << "Missing command-line arguments" << std::endl;
        return 1;
    }

    std::ifstream script_file(argv[1]);

    StringVector maze;
    if (!read_lines(script_file, maze))
    {
        std::cerr << "Cannot read script" << std::endl;
        return 1;
    }

    std::ifstream input_file(argv[2]);

    StringVector input;
    read_lines(input_file, input);

    run_maze(maze, input);

    return 0;
}