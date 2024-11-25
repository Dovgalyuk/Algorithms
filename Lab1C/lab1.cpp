#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "stack.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
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

    Stack *particle_start_coordinates = stack_create();
    std::vector<std::pair<int, int>> collisions;
    int amount_of_points = 0;
    int input_start_coordinate = 0, input_start_coordinate_rmd;
    char input_charge = ' ';

    file_input >> amount_of_points;

    for (int i = 0; i < amount_of_points; i++)
    {
        file_input >> input_start_coordinate >> input_charge;

        while (stack_empty(particle_start_coordinates) && input_charge == '-')
        {
            i++;
            input_start_coordinate_rmd = input_start_coordinate;
            file_input >> input_start_coordinate >> input_charge;

            if (input_charge == '+')
            {
                if (input_start_coordinate < input_start_coordinate_rmd)
                {
                    collisions.push_back(std::make_pair(input_start_coordinate, input_start_coordinate_rmd));

                    i++;
                    file_input >> input_start_coordinate >> input_charge;
                }
                else
                {
                    stack_push(particle_start_coordinates, input_start_coordinate);
                }

                i++;
                file_input >> input_start_coordinate >> input_charge;
            }
        }

        if (input_charge == '+')
        {
            stack_push(particle_start_coordinates, input_start_coordinate);
        }
        else if (input_charge == '-' && input_start_coordinate > stack_get(particle_start_coordinates))
        {
            collisions.push_back(std::make_pair(stack_get(particle_start_coordinates), input_start_coordinate));
            stack_pop(particle_start_coordinates);
        }
    }

    stack_delete(particle_start_coordinates);

    if(collisions.empty())
        std::cout << "None" << std::endl;

    for (const auto &particles_pair : collisions)
        std::cout << particles_pair.first << " " << particles_pair.second << std::endl;

    return 0;
}