#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include "queue.h"

using namespace std;

const int BOARD_SIZE = 8;
const int row_moves[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int column_moves[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
void search_step(Queue *positions, int distances[8][8],
                 int previous[8][8], const int other_distances[8][8],
                 int &next_count, const string board[8], int &meeting)
{
    int current_count = next_count;
    int shortest_distance = 1000;

    next_count = 0;

    for (int i = 0; i < current_count; i++)
    {
        int position = queue_get(positions);

        queue_remove(positions);

        int row = position / BOARD_SIZE;
        int column = position % BOARD_SIZE;

        for (int move = 0; move < 8; move++)
        {
            int new_row = row + row_moves[move];
            int new_column = column + column_moves[move];

            if (new_row < 0 || new_row >= BOARD_SIZE ||
                new_column < 0 || new_column >= BOARD_SIZE) 
                continue;

            if (board[new_row][new_column] == '#') 
                continue;

            if (distances[new_row][new_column] != -1) 
                continue;

            int new_position = new_row * BOARD_SIZE + new_column;

            distances[new_row][new_column] = distances[row][column] + 1;
            previous[new_row][new_column] = position;

            queue_insert(positions, new_position);
            next_count++;

            if (other_distances[new_row][new_column] != -1)
            {
                int total_distance = distances[new_row][new_column] +
                                     other_distances[new_row][new_column];
                if (total_distance < shortest_distance)
                {
                    shortest_distance = total_distance;
                    meeting = new_position;
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) 
        return 1;

    ifstream input_file(argv[1]);
    
    if (!input_file) 
        return 1;

    string board[BOARD_SIZE];

    int knight_position = -1;
    int exit_position = -1;

    for (int row = 0; row < BOARD_SIZE; row++)
    {
        if (!getline(input_file, board[row])) 
            return 1;

        if (board[row].size() == static_cast<size_t>(9) &&
            board[row][8] == '\r') board[row].pop_back();

        if (board[row].size() != static_cast<size_t>(BOARD_SIZE))
            return 1;

        for (int column = 0; column < BOARD_SIZE; column++)
        {
            if (board[row][column] == 'K')
                knight_position = row * BOARD_SIZE + column;

            if (board[row][column] == 'E')
                exit_position = row * BOARD_SIZE + column;
        }
    }

    if (knight_position == -1 || exit_position == -1) 
        return 1;

    int knight_distances[8][8], exit_distances[8][8];
    int knight_previous[8][8], exit_previous[8][8];

    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int column = 0; column < BOARD_SIZE; column++)
        {
            knight_distances[row][column] = -1;
            exit_distances[row][column] = -1;
            knight_previous[row][column] = -1;
            exit_previous[row][column] = -1;
        }
    }

    int knight_row = knight_position / BOARD_SIZE;
    int knight_column = knight_position % BOARD_SIZE;
    int exit_row = exit_position / BOARD_SIZE;
    int exit_column = exit_position % BOARD_SIZE;

    knight_distances[knight_row][knight_column] = 0;
    exit_distances[exit_row][exit_column] = 0;

    Queue *knight_queue = queue_create();
    Queue *exit_queue = queue_create();

    queue_insert(knight_queue, knight_position);
    queue_insert(exit_queue, exit_position);

    int knight_layer_count = 1;
    int exit_layer_count = 1;
    int meeting_position = -1;

    while (meeting_position == -1 &&
           !queue_empty(knight_queue) && !queue_empty(exit_queue))
    {
        search_step(knight_queue, knight_distances, knight_previous,
                    exit_distances, knight_layer_count, board, meeting_position);

        if (meeting_position == -1)
            search_step(exit_queue, exit_distances, exit_previous,
                        knight_distances, exit_layer_count, board, meeting_position);
    }

    queue_delete(knight_queue);
    queue_delete(exit_queue);

    if (meeting_position == -1) 
        return 1;

    int path[BOARD_SIZE * BOARD_SIZE];
    int path_length = 0;
    int position = meeting_position;

    while (position != -1)
    {
        path[path_length] = position;
        path_length++;
        int row = position / BOARD_SIZE;
        int column = position % BOARD_SIZE;
        position = knight_previous[row][column];
    }

    int path_number = 0;

    for (int i = path_length - 1; i >= 0; i--)
    {
        position = path[i];
        int row = position / BOARD_SIZE;
        int column = position % BOARD_SIZE;
        board[row][column] = static_cast<char>('0' + path_number);
        path_number++;
    }

    position = exit_previous[meeting_position / BOARD_SIZE]
                              [meeting_position % BOARD_SIZE];

    while (position != -1)
    {
        int row = position / BOARD_SIZE;
        int column = position % BOARD_SIZE;
        board[row][column] = static_cast<char>('0' + path_number);
        path_number++;
        position = exit_previous[row][column];
    }

    for (int row = 0; row < BOARD_SIZE; row++)
        cout << board[row] << '\n';

    return 0;
}
