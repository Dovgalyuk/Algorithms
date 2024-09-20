#include <iostream>
#include <string>
#include <new>
#include <unordered_set>
#include "queue.h"


#define queue_insert(queue, ptr) queue_insert((queue), (size_t)(ptr))
#define queue_get(queue) ((Item*)queue_get((queue)));


struct Item{
    size_t cnt = 0;
    std::string state;
    Item *previous_item = nullptr;

    Item(std::string state, Item *prev_item = nullptr)
    {
        this->state = state;
        this->previous_item = prev_item;
        this->cnt = 0;
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

    for (int x = -1; x < 2; ++x){
        for (int y = -1; y < 2; ++y){
            if (((x != 0) && (y != 0)) || ((x == 0) && (y == 0))) continue;

            row += x; col += y;
            if (((row < 3) && (row >= 0)) && ((col < 3) && (col >= 0))){
                std::string new_state = current_state;
                std::swap(new_state[zero_index], new_state[row * 3 + col]);
                states[index++] = new_state;
            }
            row -= x; col -= y;
        }
    }

    return index;
}


int main(int argc, char **argv)
{
    std::unordered_set<std::string> states;
    std::string new_states[4];
    std::string answer("123456780");
    std::string current_state(argv[1]);
    
    if (current_state == answer){
        std::cout << answer;
        return 0;
    }

    Queue *queue = queue_create();
    Item *temp_item = new Item(current_state);
    queue_insert(queue, temp_item->get_link());
    states.insert(current_state);

    while (!queue_empty(queue)){
        temp_item = queue_get(queue);
        queue_remove(queue);
        
        current_state = temp_item->state;
        int counter = get_states(current_state, new_states);
        for (int index_state = 0; index_state < counter; ++index_state){
            current_state = new_states[index_state];
            
            if (current_state == answer){
                Item *current_item = temp_item->get_link();
                temp_item->forget();
                while (true){
                    answer = current_item->state + '\n' + answer;
                    if (current_item->previous_item){
                        temp_item = current_item->previous_item->get_link();
                        current_item->forget();
                        current_item = temp_item;
                    } else {
                        current_item->forget();
                        break;
                    }
                }

                while (!queue_empty(queue)){
                    temp_item = queue_get(queue);
                    queue_remove(queue);
                    temp_item->forget();
                }

                queue_delete(queue);

                std::cout << answer;
                return 0;
            }
            
            if (states.find(current_state) == states.end()){
                Item *new_item = new Item(current_state, temp_item->get_link());
                queue_insert(queue, new_item->get_link());
                states.insert(current_state);
            }
        }
        temp_item->forget();
    }

    queue_delete(queue);

    return 0;
}
