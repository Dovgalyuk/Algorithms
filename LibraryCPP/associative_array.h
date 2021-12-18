#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H
#include<string>
struct ArrayElement;


struct associative_array;

//---------------------------------------------------------------//
associative_array* associative_array_create();

void associative_array_delete(associative_array* associative_arr);
//------------------------------------------------------------//
int hash(std::string str, int capacity);

bool str_compare(std::string str1, std::string str2); // return true if the strings are equal

int find_index(std::string key, associative_array* associative_arr);
//--------------------------------------------------------//
void insert_pair(std::string key, std::string value, associative_array* associative_arr);

std::string find(std::string key, associative_array* associative_arr);

void delete_pair(std::string key, associative_array* associative_arr);

#endif