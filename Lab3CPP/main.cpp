#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "queue.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        return 1;
    }

    string filename = argv[1];
    ifstream input_file(filename);
    if (!input_file) {
        return 1;
    }

    vector<string> maze;
    string line;
    while (getline(input_file, line)) {
        maze.push_back(line);
    }
    input_file.close();

    int height = maze.size();
    if (height == 0) {
        return 1;
    }
    int width = maze[0].size();

    int start_row = -1;
    int start_col = -1;
    for (int row = 0; row < height; ++row) {
        if (maze[row].size() != static_cast<size_t>(width)) {
            return 1;
        }
        for (int col = 0; col < width; ++col) {
            if (maze[row][col] == 'S') {
                start_row = row;
                start_col = col;
            }
        }
    }

    if (start_row == -1) {
        return 1;
    }

    vector<vector<int>> distances(height, vector<int>(width, -1));
    vector<vector<pair<int, int>>> predecessors(height, vector<pair<int, int>>(width, make_pair(-1, -1)));

    Queue* queue_instance = queue_create();
    distances[start_row][start_col] = 0;
    queue_insert(queue_instance, start_row * width + start_col);

    const int direction_rows[] = { -1, -1, 0, 0, 1, 1 };
    const int direction_cols[] = { 0, 1, -1, 1, -1, 0 };

    pair<int, int> end_position = make_pair(-1, -1);
    bool path_found = false;

    while (!queue_empty(queue_instance)) {
        int encoded_position = queue_get(queue_instance);
        queue_remove(queue_instance);

        int current_row = encoded_position / width;
        int current_col = encoded_position % width;

        if (maze[current_row][current_col] == 'E') {
            path_found = true;
            end_position = make_pair(current_row, current_col);
            break;
        }

        for (int direction = 0; direction < 6; ++direction) {
            int next_row = current_row + direction_rows[direction];
            int next_col = current_col + direction_cols[direction];

            if (next_row >= 0 && next_row < height && next_col >= 0 && next_col < width &&
                distances[next_row][next_col] == -1 && maze[next_row][next_col] != '#') {
                distances[next_row][next_col] = distances[current_row][current_col] + 1;
                predecessors[next_row][next_col] = make_pair(current_row, current_col);
                queue_insert(queue_instance, next_row * width + next_col);
            }
        }
    }

    queue_delete(queue_instance);

    if (!path_found) {
        cout << -1 << endl;
        return 0;
    }

    vector<pair<int, int>> path_positions;
    pair<int, int> current_position = end_position;
    while (current_position.first != -1) {
        path_positions.push_back(current_position);
        if (current_position.first == start_row && current_position.second == start_col) {
            break;
        }
        current_position = predecessors[current_position.first][current_position.second];
    }
    reverse(path_positions.begin(), path_positions.end());

    int path_length = path_positions.size();
    cout << path_length << endl;

    cout << "Path: ";
    for (size_t index = 0; index < path_positions.size(); ++index) {
        pair<int, int> position = path_positions[index];
        cout << "(" << position.second << "," << position.first << ")";
        if (index < path_positions.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    for (size_t index = 1; index < path_positions.size() - 1; ++index) {
        pair<int, int> position = path_positions[index];
        maze[position.first][position.second] = 'x';
    }

    cout << "Maze with path:" << endl;

    // Print top border with indent 0
    string top_border = " /";
    for (int column = 1; column < width; ++column) {
        top_border += " \\ /";
    }
    top_border += " \\";
    cout << top_border << endl;

    const int indent_increment = 2;
    for (int row = 0; row < height; ++row) {
        // Print cell line
        string cell_line = string(row * indent_increment, ' ') + "|";
        for (int column = 0; column < width; ++column) {
            char display_char = (maze[row][column] == '.') ? ' ' : maze[row][column];
            cell_line += " " + string(1, display_char) + " |";
        }
        cout << cell_line << endl;

        // Print bottom border
        string bottom_border = string(row * indent_increment, ' ') + " \\";
        for (int column = 1; column < width; ++column) {
            bottom_border += " / \\";
        }
        bottom_border += " /";
        cout << bottom_border << endl;
    }

    return 0;
}