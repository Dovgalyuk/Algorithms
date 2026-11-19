#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "queue.h"

static const Data CELL_WALL = 0;
static const Data CELL_EMPTY = 1;
static const Data CELL_START = 2;
static const Data CELL_VISITED = 3;

static Data char_to_cell(char c)
{
    if (c == '#') return CELL_WALL;
    if (c == '.') return CELL_EMPTY;
    if (c == 'X') return CELL_START;
    return (Data)-1;
}

static char cell_to_char(Data cell)
{
    if (cell == CELL_WALL) return '#';
    if (cell == CELL_EMPTY) return '.';
    if (cell == CELL_START) return 'X';
    if (cell == CELL_VISITED) return 'x';
    return '?';
}

struct Maze
{
    Vector *cells;
    int rows;
    int cols;
};

static void maze_create(Maze &maze)
{
    maze.cells = vector_create();
    maze.rows = 0;
    maze.cols = 0;
}

static void maze_delete(Maze &maze)
{
    vector_delete(maze.cells);
    maze.cells = nullptr;
    maze.rows = 0;
    maze.cols = 0;
}

static Data maze_get(const Maze &maze, int r, int c)
{
    return vector_get(maze.cells, (size_t)r * (size_t)maze.cols + (size_t)c);
}

static void maze_set(Maze &maze, int r, int c, Data value)
{
    vector_set(maze.cells, (size_t)r * (size_t)maze.cols + (size_t)c, value);
}

static bool read_maze(const char *filename, Maze &maze)
{
    std::ifstream input(filename);
    if (!input.is_open())
    {
        std::cerr << "Error opening file: " << filename << "\n";
        return false;
    }

    std::string line;
    int rows = 0;
    int cols = -1;
    bool first = true;

    while (std::getline(input, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (line.empty())
            continue;

        if (first)
        {
            cols = (int)line.size();
            first = false;
        }
        else if ((int)line.size() != cols)
        {
            std::cerr << "Error: row " << rows << " has different length\n";
            return false;
        }

        for (size_t c = 0; c < line.size(); c++)
        {
            if (char_to_cell(line[c]) < 0)
            {
                std::cerr << "Error: invalid character '"
                          << line[c] << "' in maze\n";
                return false;
            }
        }
        rows++;
    }

    if (rows == 0 || cols <= 0)
    {
        std::cerr << "Error: empty maze\n";
        return false;
    }

    input.clear();
    input.seekg(0, std::ios::beg);

    maze.rows = rows;
    maze.cols = cols;
    vector_resize(maze.cells, (size_t)rows * (size_t)cols);

    int r = 0;
    while (std::getline(input, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (line.empty())
            continue;

        for (int c = 0; c < cols; c++)
        {
            maze_set(maze, r, c, char_to_cell(line[c]));
        }
        r++;
    }

    return true;
}

static bool find_start(const Maze &maze, int &start_r, int &start_c)
{
    start_r = -1;
    start_c = -1;

    for (int r = 0; r < maze.rows; r++)
    {
        for (int c = 0; c < maze.cols; c++)
        {
            if (maze_get(maze, r, c) == CELL_START)
            {
                if (start_r != -1)
                {
                    std::cerr << "Error: more than one start 'X'\n";
                    return false;
                }
                start_r = r;
                start_c = c;
            }
        }
    }

    if (start_r == -1)
    {
        std::cerr << "Error: no start 'X'\n";
        return false;
    }

    return true;
}

static int solve(Maze &maze, int start_r, int start_c)
{
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    Queue *q = queue_create();
    maze_set(maze, start_r, start_c, CELL_VISITED);
    queue_insert(q, (Data)start_r * (Data)maze.cols + (Data)start_c);

    int reachable = 0;
    while (!queue_empty(q))
    {
        Data pos = queue_get(q);
        queue_remove(q);
        reachable++;

        int r = (int)(pos / (Data)maze.cols);
        int c = (int)(pos % (Data)maze.cols);

        for (int k = 0; k < 4; k++)
        {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (nr < 0 || nr >= maze.rows) continue;
            if (nc < 0 || nc >= maze.cols) continue;
            if (maze_get(maze, nr, nc) != CELL_EMPTY) continue;

            maze_set(maze, nr, nc, CELL_VISITED);
            queue_insert(q, (Data)nr * (Data)maze.cols + (Data)nc);
        }
    }

    queue_delete(q);
    return reachable;
}

static void print_maze(const Maze &maze)
{
    for (int r = 0; r < maze.rows; r++)
    {
        for (int c = 0; c < maze.cols; c++)
            std::cout << cell_to_char(maze_get(maze, r, c));
        std::cout << "\n";
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <maze_file>\n";
        return 2;
    }

    Maze maze;
    maze_create(maze);

    if (!read_maze(argv[1], maze))
    {
        maze_delete(maze);
        return 1;
    }

    int start_r, start_c;
    if (!find_start(maze, start_r, start_c))
    {
        maze_delete(maze);
        return 1;
    }

    int reachable = solve(maze, start_r, start_c);

    std::cout << reachable << "\n";
    print_maze(maze);

    maze_delete(maze);
    return 0;
}