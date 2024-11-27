#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "queue.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "args error" << std::endl;
        return 1;
    }

    std::ifstream file_input(argv[1]);
    if (!file_input)
    {
        std::cerr << "read file error " << argv[1] << std::endl;
        return 1;
    }

    Queue* number_1 = queue_create();
    Queue* number_2 = queue_create();
    Queue* adding_result = queue_create();

    int lenght_of_number = 0;
    int carry = 0;
    int temp_var_2_push = 0;

    file_input >> lenght_of_number;

    for (int i = 0; i < lenght_of_number; i++)
    {
        file_input >> temp_var_2_push;
        queue_insert(number_1, temp_var_2_push);
    }

    for (int i = 0; i < lenght_of_number; i++)
    {
        file_input >> temp_var_2_push;
        queue_insert(number_2, temp_var_2_push);
    }

    file_input.close();

    while (!queue_empty(number_1) && !queue_empty(number_2))
    {
        temp_var_2_push = queue_get(number_1) + queue_get(number_2) + carry;
        queue_remove(number_1);
        queue_remove(number_2);

        queue_insert(adding_result, temp_var_2_push % 10);
        carry = temp_var_2_push / 10;
    }

    queue_delete(number_1);
    queue_delete(number_2);

    if(carry > 0)
    {
        queue_insert(adding_result, carry);
    }

    std::ofstream file_output(argv[2]);

    if (!file_output)
    {
        std::cerr << "output file error " << argv[2] << std::endl;
        return 1;
    }

    while (!queue_empty(adding_result))
    {
        // std::cout << queue_get(adding_result) << std::endl;
        file_output << queue_get(adding_result) << "\n";
        queue_remove(adding_result);
    }

    queue_delete(adding_result);
}