#include <iostream>
#include <unordered_map>
#include <cmath>
#include <iomanip>
#include "vector.h"
#include "queue.h"

constexpr size_t pow10(size_t n) 
{
    size_t ans = 1;
    for (size_t ind{0}; ind < n; ++ind) 
        ans *= 10;
    return ans;
}

unsigned int get_digit(size_t num, size_t ind)
{
    constexpr size_t data[] {pow10(0), pow10(1), pow10(2),
                             pow10(3), pow10(4), pow10(5),
                             pow10(6), pow10(7), pow10(8)};
    num /= data[ind];
    return num % 10;
}

size_t get_states(size_t current_state, size_t *states)
{
    size_t index = 0;
    size_t zero_index = 0;

    while (get_digit(current_state, zero_index))
        zero_index++;

    size_t row = zero_index / 3;
    size_t col = zero_index % 3;
    size_t new_state;
    int new_row, new_col, new_index;

    for (int x = -1; x < 2; ++x){
        for (int y = -1; y < 2; ++y){
            if (std::abs(x) == std::abs(y)) continue;

            new_row = row + y; new_col = col + x;
            new_index = new_row * 3 + new_col;
            if ((0 <= new_row) && (new_row < 3) && (0 <= new_col) && (new_col < 3)) {
                new_state = current_state + get_digit(current_state, new_index) * (pow10(zero_index) - pow10(new_index));
                states[index++] = new_state;
            }
        }
    }

    return index;
}

void show_answer(size_t state, std::unordered_map<size_t, size_t> &all_states)
{
    size_t index = 0;
    Vector *vec = vector_create();
    vector_resize(vec, 32);  // The God number for the 3x3 sliding puzzle is 31

    while (state) {
        vector_set(vec, index++, state);
        state = all_states[state];
    }

    for (size_t ind{index}; ind > 0; --ind)
        std::cout << std::setw(9) << std::setfill('0') << vector_get(vec, ind - 1) << std::endl;
    vector_delete(vec);
}

int search_solution(Queue *queue, size_t target_state, std::unordered_map<size_t, size_t> &all_states)
{
    size_t states[4];
    size_t cnt;
    size_t state;

    while (!queue_empty(queue)){
        state = queue_get(queue);
        cnt = get_states(state, states);
        queue_remove(queue);

        for (size_t ind{0}; ind < cnt; ++ind){
            if (states[ind] == target_state){
                all_states.emplace(states[ind], state);
                return 1;
            } else if (!all_states.count(states[ind])) {
                all_states.emplace(states[ind], state);
                queue_insert(queue, states[ind]);
            }
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    char *ptr = argv[1];
    size_t target_state = 123456780;
    size_t first_state = 0;
    size_t ans;
    while (*ptr >= '0' && *ptr <= '9')
        first_state = 10 * first_state + (*ptr++ - '0');

    Queue *queue = queue_create();
    std::unordered_map<size_t, size_t> all_states;
    queue_insert(queue, first_state);
    all_states.emplace(first_state, 0);
    
    if (first_state == target_state){
        std::cout << target_state;
    } else {
        ans = search_solution(queue, target_state, all_states);
        if (ans)
            show_answer(target_state, all_states);
    }

    queue_delete(queue);

    return 0;
}