#include<iostream>
#include<string>
#include "associative_array.h"


int main()
{
	associative_array* associative_arr = associative_array_create();
	int load_test_count = 1000000; 

	for (int i = 0; i < load_test_count; i++)
	{
		insert_pair(std::to_string(i), std::to_string(i), associative_arr);
	}

	for (int i = 100; i < 120; i++)
	{
		if (find(std::to_string(i), associative_arr) != std::to_string(i))
		{
			std::cout << "Search or insert error";
			return 1;
		}
	}

	for (int i = 0; i < load_test_count; i++)
	{
		delete_pair(std::to_string(i), associative_arr);
	}

	for (int i = 100; i < 120; i++)
	{
		if (find(std::to_string(i), associative_arr) != "")
		{
			std::cout << "Delete error";
			return 1;
		}
	}

	associative_array_delete(associative_arr);
}