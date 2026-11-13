#include "fish.h"

void interpretation(Fish &f, char c)
{
    string NCHARS = "0123456789abcdef";

    if (f.q != 0)
    {
        if (c == f.q)
        {
            f.q = 0;
        }
        else
        {
            push(f, c);
        }
        return;
    }

    int n = NCHARS.find(c);
    if (n != -1)
    {
        push(f, n);
        return;
    }

    switch (c)
    {
        case '>':
            fish_right(f);
            break;
        case '<':
            fish_left(f);
            break;
        case '^':
            fish_up(f);
            break;
        case 'v':
            fish_down(f);
            break;
        case '/':
            fish_mirror_slash(f);
            break;
        case '\\':
            fish_mirror_backslash(f);
            break;
        case '|':
            fish_mirror_vertical(f);
            break;
        case '_':
            fish_mirror_horizontal(f);
            break;
        case '#':
            fish_mirror_both(f);
            break;
        case 'x':
            fish_random_direction(f);
            break;
        case '!':
            fish_trampoline(f);
            break;
        case '?':
            fish_trampoline_conditional(f);
            break;
        case '.':
            fish_jump(f);
            break;
        case '+':
            fish_add(f);
            break;
        case '-':
            fish_sub(f);
            break;
        case '*':
            fish_mul(f);
            break;
        case ',':
            fish_div(f);
            break;
        case '%':
            fish_mod(f);
            break;
        case '=':
            fish_equal(f);
            break;
        case ')':
            fish_greater(f);
            break;
        case '(':
            fish_less(f);
            break;
        case '"':
        case '\'':
            f.q = c;
            break;
        case ':':
            fish_duplicate(f);
            break;
        case '~':
            fish_remove(f);
            break;
        case '$':
            fish_swap_two(f);
            break;
        case '@':
            fish_swap_three(f);
            break;
        case '}':
            fish_shift_right(f);
            break;
        case '{':
            fish_shift_left(f);
            break;
        case 'r':
            fish_reverse(f);
            break;
        case 'l':
            fish_length(f);
            break;
        case '[':
            fish_stack_create(f);
            break;
        case ']':
            fish_stack_remove(f);
            break;
        case 'o':
            fish_output_char(f);
            break;
        case 'n':
            fish_output_num(f);
            break;
        case 'i':
            fish_input(f);
            break;
        case '&':
            fish_register(f);
            break;
        case 'g':
            fish_cell_get(f);
            break;
        case 'p':
            fish_cell_put(f);
            break;
        case ';':
            exit(0);
        case ' ':
            break;

        default:
            error();
    }
}

void read_script(Fish &f, const string &path)
{
    ifstream script(path);
    string line;

    while (getline(script, line))
    {
        f.grid.push_back(line);
        if ((int)line.size() > f.w)
        {
            f.w = line.size();
        }
    }
    f.h = f.grid.size();

    for (int i = 0; i < f.h; ++i)
    {
        while ((int)f.grid[i].size() < f.w)
        {
            f.grid[i] += ' ';
        }
    }
}

void run(Fish &f)
{
    while (true)
    {
        interpretation(f, f.grid[f.y][f.x]);
        move(f);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Use: ./fish script.fish input.txt" << endl;
        return 1;
    }

    Fish f;
    read_script(f, argv[1]);
    f.input.open(argv[2]);

    if (f.w == 0)
    {
        return 0;
    }

    f.stacks.push_back(stack_create());
    run(f);
}
