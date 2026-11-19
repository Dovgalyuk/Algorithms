#include <fstream>
#include <iostream>
#include <string>
#include "queue.h"

using namespace std;

const int SIZE = 8;
const int dr[8] = {2, 2, 1, 1, -1, -1, -2, -2};
const int dc[8] = {1, -1, 2, -2, 2, -2, 1, -1};

int expand_level(Queue* queue, const string board[SIZE],
                 int distance[], int parent[], const int other_distance[])
{
    int level = distance[queue_get(queue)];

    while (!queue_empty(queue) && distance[queue_get(queue)] == level)
    {
        int current = queue_get(queue);
        queue_remove(queue);

        for (int move = 0; move < 8; move++)
        {
            int row = current / SIZE + dr[move];
            int col = current % SIZE + dc[move];

            if (row < 0 || row >= SIZE || col < 0 || col >= SIZE ||
                board[row][col] == '#')
            {
                continue;
            }

            int next = row * SIZE + col;
            if (distance[next] != -1)
            {
                continue;
            }

            distance[next] = level + 1;
            parent[next] = current;
            if (other_distance[next] != -1)
            {
                return next;
            }
            queue_insert(queue, next);
        }
    }
    return -1;
}

char path_symbol(int step)
{
    if (step < 10)
    {
        return '0' + step;
    }
    return 'a' + step - 10;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    ifstream file(argv[1]);
    if (!file)
    {
        return 1;
    }

    string board[SIZE];
    int start = -1;
    int finish = -1;

    for (int row = 0; row < SIZE; row++)
    {
        if (!(file >> board[row]) || board[row].size() != SIZE)
        {
            return 1;
        }

        for (int col = 0; col < SIZE; col++)
        {
            if (board[row][col] == 'K')
            {
                start = row * SIZE + col;
            }
            if (board[row][col] == 'E')
            {
                finish = row * SIZE + col;
            }
        }
    }
    if (start == -1 || finish == -1)
    {
        return 1;
    }

    int distance[2][SIZE * SIZE];
    int parent[2][SIZE * SIZE];
    for (int side = 0; side < 2; side++)
    {
        for (int cell = 0; cell < SIZE * SIZE; cell++)
        {
            distance[side][cell] = -1;
            parent[side][cell] = -1;
        }
    }

    Queue* queues[2] = {queue_create(), queue_create()};
    distance[0][start] = 0;
    distance[1][finish] = 0;
    queue_insert(queues[0], start);
    queue_insert(queues[1], finish);

    int meeting = -1;
    int turn = 0;
    while (meeting == -1 && !queue_empty(queues[0]) && !queue_empty(queues[1]))
    {
        meeting = expand_level(queues[turn], board, distance[turn],
                               parent[turn], distance[1 - turn]);
        turn = 1 - turn;
    }
    queue_delete(queues[0]);
    queue_delete(queues[1]);

    if (meeting != -1)
    {
        int step = distance[0][meeting];

        for (int cell = meeting; cell != -1; cell = parent[0][cell])
        {
            board[cell / SIZE][cell % SIZE] = path_symbol(step);
            step--;
        }

        step = distance[0][meeting] + 1;
        for (int cell = parent[1][meeting]; cell != -1; cell = parent[1][cell])
        {
            board[cell / SIZE][cell % SIZE] = path_symbol(step);
            step++;
        }
    }

    for (int row = 0; row < SIZE; row++)
    {
        cout << board[row] << '\n';
    }
    return 0;
}
