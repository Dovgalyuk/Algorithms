#include <iostream>
#include <string>
#include <new>
#include <unordered_set>
#include "queue.h"

#define abs(x) (((x) >= 0) ? (x) : (-(x)))
#define queue_insert(queue, ptr) queue_insert((queue), (Data)(ptr))
#define queue_get(queue) ((Item*)queue_get((queue)))


struct Item{
    size_t cnt = 0;
    std::string state;
    Item *previous_item = nullptr;

    Item(std::string state, Item *prev_item = nullptr)
    {
        this->state = state;
        this->previous_item = prev_item;
        this->cnt = 1;
    }

    Item *get_link()
    {
        cnt++;
        return this;
    }

    void forget()
    {
        if (cnt) cnt--;
        if (!cnt){
            if (previous_item) previous_item->forget();
            delete this;
        };
    }
};


int get_states(std::string current_state, std::string *states)
{
    int index = 0;
    int zero_index = current_state.find('0');
    int row = zero_index / 3;
    int col = zero_index % 3;
    int new_row, new_col;

    for (int x = -1; x < 2; ++x){
        for (int y = -1; y < 2; ++y){
            if (abs(x) == abs(y)) continue;

            new_row = row + y; new_col = col + x;
            if (((new_row < 3) && (new_row >= 0)) && ((new_col < 3) && (new_col >= 0))){
                std::string new_state = current_state;
                std::swap(new_state[zero_index], new_state[new_row * 3 + new_col]);
                states[index++] = new_state;
            }
        }
    }

    return index;
}

void show_answer(Item *last_item)
{
    std::string answer = "";

    while (last_item){
        answer = last_item->state + '\n' + answer;
        last_item = last_item->previous_item;
    }

    std::cout << answer;
}

void delete_all_items(Queue *queue)
{
    Item *ptr = nullptr;
    while (!queue_empty(queue)){
        ptr = queue_get(queue);
        queue_remove(queue);
        ptr->forget();
    }
}

Item *search_solution(Queue *queue, std::string first_state, std::string target_state)
{
    Item *temp_item = nullptr;
    Item *answer_item = nullptr;
    std::unordered_set<std::string> states;
    std::string new_states[4];
    std::string current_state;

    queue_insert(queue, new Item(first_state));
    states.insert(first_state);
    while (!queue_empty(queue) && !answer_item){
        temp_item = queue_get(queue);
        queue_remove(queue);
        
        int counter = get_states(temp_item->state, new_states);
        for (int index_state = 0; index_state < counter; ++index_state){
            current_state = new_states[index_state];
            
            if (current_state == target_state){
                answer_item = new Item(current_state, temp_item->get_link());
                break;
            }
            
            if (states.find(current_state) == states.end()){
                Item *new_item = new Item(current_state, temp_item->get_link());
                queue_insert(queue, new_item);
                states.insert(current_state);
            }
        }

        temp_item->forget();
    }

    return answer_item;
}

int main(int argc, char **argv)
{
    Item *ans = nullptr;
    std::string target_state("123456780");
    std::string first_state(argv[1]);

    Queue *queue = queue_create();
    
    if (first_state == target_state){
        std::cout << target_state;
    } else {
        ans = search_solution(queue, first_state, target_state);
        if (ans){
            show_answer(ans);
            ans->forget();
        }
    }

    delete_all_items(queue);
    queue_delete(queue);

    return 0;
}
