#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

int main(int, char **argv)
{
    std::ifstream input(argv[1]);
    
    char maze[100][100];
    int rows = 0;
    int cols = 0;
    
    std::string line;
    while (std::getline(input, line))
    {
        cols = (int)line.size();
        for (int j = 0; j < cols; j++)
        {
            maze[rows][j] = line[j];
        }
        rows++;
    }
    input.close();
    
    int start_row = -1, start_col = -1;
    int end_row = -1, end_col = -1;
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (maze[i][j] == 'X')
            {
                start_row = i;
                start_col = j;
            }
            if (maze[i][j] == 'Y')
            {
                end_row = i;
                end_col = j;
            }
        }
    }
    
    int dist[100][100];
    int parent_row[100][100];
    int parent_col[100][100];
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            dist[i][j] = -1;
        }
    }
    
    Queue *q = queue_create();
    queue_insert(q, start_row * 1000 + start_col);
    dist[start_row][start_col] = 0;
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    while (!queue_empty(q))
    {
        int code = queue_get(q);
        queue_remove(q);
        
        int cur_row = code / 1000;
        int cur_col = code % 1000;
        
        for (int i = 0; i < 4; i++)
        {
            int new_row = cur_row + dr[i];
            int new_col = cur_col + dc[i];
            
            if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols)
            {
                if ((maze[new_row][new_col] == '.' || maze[new_row][new_col] == 'Y') && dist[new_row][new_col] == -1)
                {
                    dist[new_row][new_col] = dist[cur_row][cur_col] + 1;
                    parent_row[new_row][new_col] = cur_row;
                    parent_col[new_row][new_col] = cur_col;
                    queue_insert(q, new_row * 1000 + new_col);
                }
            }
        }
    }
    
    queue_delete(q);
    
    if (dist[end_row][end_col] == -1)
    {
        std::cout << "IMPOSSIBLE" << std::endl;
    }
    else
    {
        int cur_row = end_row;
        int cur_col = end_col;
        
        while (!(cur_row == start_row && cur_col == start_col))
        {
            if (maze[cur_row][cur_col] == '.')
            {
                maze[cur_row][cur_col] = 'x';
            }
            int temp_row = parent_row[cur_row][cur_col];
            int temp_col = parent_col[cur_row][cur_col];
            cur_row = temp_row;
            cur_col = temp_col;
        }
        
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << maze[i][j];
            }
            std::cout << std::endl;
        }
    }
    
    return 0;
}
