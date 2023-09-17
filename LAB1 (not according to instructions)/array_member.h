#pragma once

#include <iostream>
#include <vector>
#include <set>

class array_member
{
private:
    int data;

    array_member* tail_of_array;
    array_member* head_of_array;
    array_member* pointer_to_next;
    array_member* pointer_to_previous;
    
    int set_data();
    void get_data(array_member* current_array_member);
    int randomize(int n);
    void retail(array_member* current_array_member);

public:
    array_member();

    void create_array_member(array_member* currernt_array_member, int additional_information);
    void rnd_fill_array(array_member* current_array_member, int input_array_size);
    void print_array(array_member* current_array_member);
    void delete_array(array_member* current_array_member);

    int array_processing_1(array_member* current_array_member, int iterator, int& result);
    void array_processing_2(array_member* current_array_member, std::set <int>& numbers_wout_repeat);
};