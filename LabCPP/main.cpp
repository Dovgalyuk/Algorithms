#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include "queue.h"

using namespace std;

#pragma region ConstantsAndStructs

const string GOAL = "123456780";
const int SIZE = 3;

struct State
{
    string value;
    int parent_index;
};

#pragma endregion

#pragma region Logic

vector<string> get_neighbors(const string& current)
{
    vector<string> result;
    size_t zero_pos = current.find('0');
    int x = static_cast<int>(zero_pos % SIZE);
    int y = static_cast<int>(zero_pos / SIZE);

    const int dx[] = { -1, 1, 0, 0 };
    const int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; ++i)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE)
        {
            size_t swap_pos = ny * SIZE + nx;
            string next = current;
            swap(next[zero_pos], next[swap_pos]);
            result.push_back(next);
        }
    }
    return result;
}

vector<string> reconstruct_path(const vector<State>& states, int index)
{
    vector<string> path;
    while (index != -1)
    {
        path.push_back(states[index].value);
        index = states[index].parent_index;
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<string> solve_puzzle(const string& start)
{
    Queue* queue = queue_create();
    unordered_set<string> visited;
    vector<State> states;

    states.push_back({ start, -1 });
    queue_insert(queue, 0);
    visited.insert(start);

    while (!queue_empty(queue))
    {
        int current_index = queue_get(queue);
        queue_remove(queue);

        const string& current_state = states[current_index].value;
        if (current_state == GOAL)
        {
            queue_delete(queue);
            return reconstruct_path(states, current_index);
        }

        for (const string& neighbor : get_neighbors(current_state))
        {
            if (visited.count(neighbor) == 0)
            {
                visited.insert(neighbor);
                states.push_back({ neighbor, current_index });
                queue_insert(queue, static_cast<int>(states.size()) - 1);
            }
        }
    }

    queue_delete(queue);
    return {};
}

#pragma endregion

#pragma region ExecutionAndDisplay

bool validation(const string& s)
{
    if (s.length() != 9) return false;

    unordered_set<char> digits;
    for (char c : s) {
        if (!isdigit(c)) return false;
        digits.insert(c);
    }

    return digits.size() == 9;
}

void display(const string& board)
{
    for (int i = 0; i < SIZE; ++i)
    {
        cout << "|";
        for (int j = 0; j < SIZE; ++j)
        {
            char tile = board[i * SIZE + j];
            cout << (tile == '0' ? "   " : " " + string(1, tile) + " ") << "|";
        }
        cout << endl;
        if (i < SIZE - 1) {
            cout << "+---+---+---+" << endl;
        }
    }
    cout << endl;
}

string get_input(int argc, char* argv[])
{
    string input;
    if (argc >= 2)
    {
        ifstream input_file(argv[1]);
        if (!input_file)
        {
            cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
            exit(1);
        }
        input_file >> input;
    }
    else
    {
        cin >> input;
    }

    if (!validation(input))
    {
        cerr << "Ошибка: некорректные входные данные" << endl;
        exit(1);
    }

    return input;
}
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
    string input = get_input(argc, argv);
    vector<string> solution = solve_puzzle(input);

    if (solution.empty())
    {
        cout << "Решение не найдено." << endl;
    }
    else
    {
        cout << "Количество шагов: " << solution.size() - 1 << endl;
        for (const string& state : solution)
        {
            display(state);
        }
    }

    return 0;
}

#pragma endregion
