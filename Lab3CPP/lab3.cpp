#include <iostream>
#include <unordered_map>
#include <cmath>
#include <iomanip>
#include "vector.h"
#include "queue.h"

size_t get_figure(size_t num, size_t ind){
    num /= std::pow(10, ind);
    return num % 10;
}

size_t get_states(size_t current_state, size_t *states)
{
    size_t index = 0;
    size_t zero_index = 0;

    while (get_figure(current_state, zero_index))
        zero_index++;

    size_t row = zero_index / 3;
    size_t col = zero_index % 3;
    size_t new_row, new_col, new_index, new_state, figure;

    for (int x = -1; x < 2; ++x){
        for (int y = -1; y < 2; ++y){
            if (std::abs(x) == std::abs(y)) continue;

            new_row = row + y; new_col = col + x;
            new_index = new_row * 3 + new_col;
            if ((new_row < 3) && (new_col < 3)){
                figure = get_figure(current_state, new_index);
                new_state = current_state + figure * std::pow(10, zero_index) - figure * std::pow(10, new_index);
                states[index++] = new_state;
            }
        }
    }

    return index;
}

void show_answer(size_t first_state, size_t state, std::unordered_map<size_t, size_t> *all_states)
{
    size_t index = 0;
    size_t states[4];
    size_t count = (*all_states)[state];
    size_t cnt;
    Vector *vec = vector_create();
    vector_resize(vec, count);

    while (true){
        vector_set(vec, index++, state);
        count--;
        if (!count) break;

        cnt = get_states(state, states);
        for (size_t ind{0}; ind < cnt; ++ind){
            if ((*all_states).count(states[ind])){
                if ((*all_states)[states[ind]] == count)
                    state = states[ind];
            }
        }
    }

    for (size_t ind{vector_size(vec)}; ind > 0; --ind)
        std::cout << std::setw(9) << std::setfill('0') << vector_get(vec, ind - 1) << std::endl;
    vector_delete(vec);
}

int search_solution(Queue *queue, size_t target_state, std::unordered_map<size_t, size_t> *all_states)
{
    size_t states[4];
    size_t cnt;
    size_t state;
    size_t level = 1;

    while (!queue_empty(queue)){
        state = queue_get(queue);
        level = (*all_states)[state] + 1;
        cnt = get_states(state, states);
        queue_remove(queue);

        for (size_t ind{0}; ind < cnt; ++ind){
            state = states[ind];

            if (state == target_state){
                all_states->emplace(state, level);
                return 1;
            } else if (!(*all_states).count(state)) {
                all_states->emplace(state, level);
                queue_insert(queue, state);
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
    all_states.emplace(first_state, 1);
    
    if (first_state == target_state){
        std::cout << target_state;
    } else {
        ans = search_solution(queue, target_state, &all_states);
        if (ans)
            show_answer(first_state, target_state, &all_states);
    }

    queue_delete(queue);

    return 0;
}

