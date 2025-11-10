#include "queue.h"
#include "vector.h"

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void print_state(const std::string& board, size_t step, size_t total_steps)
{
    std::cout << "Шаг " << step << ":\n";
    for (int row = 0; row < 3; ++row)
    {
        int base = row * 3;
        std::cout << board[base] << ' ' << board[base + 1] << ' ' << board[base + 2] << '\n';
    }
    if (step + 1 < total_steps)
    {
        std::cout << "---\n";
    }
}

bool is_solvable(const std::string& s)
{
    int inversions = 0;
    for (size_t i = 0; i < s.size(); ++i)
    {
        if (s[i] == '0')
        {
            continue;
        }
        for (size_t j = i + 1; j < s.size(); ++j)
        {
            if (s[j] == '0')
            {
                continue;
            }
            if (s[i] > s[j])
            {
                ++inversions;
            }
        }
    }
    return (inversions % 2) == 0;
}

bool can_swap(int from, int to)
{
    if (to < 0 || to >= 9)
    {
        return false;
    }

    int from_row = from / 3;
    int from_col = from % 3;
    int to_row = to / 3;
    int to_col = to % 3;
    int row_diff = from_row > to_row ? from_row - to_row : to_row - from_row;
    int col_diff = from_col > to_col ? from_col - to_col : to_col - from_col;
    return (row_diff + col_diff) == 1;
}

int main(int argc, char const* argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in)
    {
        return 1;
    }

    std::string input;
    if (!(in >> input) || input.size() != 9)
    {
        return 1;
    }

    std::array<bool, 9> seen{};
    for (char c : input)
    {
        if (c < '0' || c > '8')
        {
            return 1;
        }
        size_t idx = static_cast<size_t>(c - '0');
        if (seen[idx])
        {
            return 1;
        }
        seen[idx] = true;
    }

    if (!is_solvable(input))
    {
        std::cout << "Нет решения\n";
        return 0;
    }

    const std::string start = input;
    const std::string goal = "123456780";

    if (start == goal)
    {
        print_state(start, 0, 1);
        return 0;
    }

    Vector parents;
    std::vector<std::string> boards;

    auto append_state = [&](const std::string& board, int parent_idx) -> size_t {
        size_t idx = boards.size();
        boards.push_back(board);
        parents.resize(idx + 1);
        parents.set(idx, parent_idx);
        return idx;
        };

    size_t start_idx = append_state(start, -1);
    std::unordered_map<std::string, size_t> visited;
    visited[start] = start_idx;

    Queue q;
    q.insert(static_cast<Data>(start_idx));

    const int moves[] = { -1, 1, -3, 3 };
    bool found = false;
    size_t goal_idx = start_idx;

    while (!q.empty())
    {
        size_t idx = static_cast<size_t>(q.get());
        q.remove();
        const std::string& board = boards[idx];
        int zero_pos = static_cast<int>(board.find('0'));

        for (int delta : moves)
        {
            int next_zero = zero_pos + delta;
            if (!can_swap(zero_pos, next_zero))
            {
                continue;
            }

            std::string next_board = board;
            std::swap(next_board[zero_pos], next_board[next_zero]);

            if (visited.count(next_board))
            {
                continue;
            }

            size_t new_idx = append_state(next_board, static_cast<int>(idx));
            visited[next_board] = new_idx;
            q.insert(static_cast<Data>(new_idx));

            if (next_board == goal)
            {
                found = true;
                goal_idx = new_idx;
                break;
            }
        }

        if (found)
        {
            break;
        }
    }

    if (!found)
    {
        std::cout << "Нет решения\n";
        return 0;
    }

    Vector path;
    size_t cursor = goal_idx;
    while (true)
    {
        size_t sz = path.size();
        path.resize(sz + 1);
        path.set(sz, static_cast<Data>(cursor));

        int parent_idx = parents.get(cursor);
        if (parent_idx < 0)
        {
            break;
        }
        cursor = static_cast<size_t>(parent_idx);
    }

    size_t total_steps = path.size();
    for (int i = static_cast<int>(path.size()) - 1; i >= 0; --i)
    {
        size_t step_idx = static_cast<size_t>(total_steps - 1 - i);
        size_t board_idx = static_cast<size_t>(path.get(static_cast<size_t>(i)));
        print_state(boards[board_idx], step_idx, total_steps);
    }

    return 0;
}
