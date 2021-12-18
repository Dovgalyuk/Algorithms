#include "associative_array.h"
#include "../LibraryCPPTemplate/array.h" 
#include<string>

struct ArrayElement
{
	std::string key;
	std::string value;
};

struct associative_array
{
	int capacity = 23;
	int size = 0;
	Array<ArrayElement>* arr;
	associative_array()
	{
		arr = new Array<ArrayElement>(capacity);
	}
	~associative_array()
	{
		delete arr;
	}
};
//---------------------------------------------------------------//

associative_array* associative_array_create()
{
	return new associative_array();
}

void associative_array_delete(associative_array* associative_arr)
{
	delete associative_arr;
}
//------------------------------------------------------------// secondary functions

int hash(std::string str, int capacity)
{
	int sum = 0;
	for (int p = 0, i = 0; i < str.size(); i++, p++)
	{
		if (p > 12) p = 0;
		sum += (str[i] * (long long)pow(31, p)) % capacity;
	}
	return sum % capacity;
}

bool str_compare(std::string str1, std::string str2) // return true if the strings are equal
{
	if (str1.size() != str2.size())
		return false;
	int matching_letter = 0;
	for (int i = 0; i < str1.size(); i++)
	{
		if (str1[i] != str2[i])
			return false;
	}
	return true;
}

int find_index(std::string key, associative_array* associative_arr)
{
	int Index = hash(key, associative_arr->capacity);
	if (associative_arr->arr->get(Index).key.size() != 0)
	{
		while (associative_arr->arr->get(Index).key.size() != 0)
		{
			std::string find = associative_arr->arr->get(Index).value;
			if (str_compare(key, associative_arr->arr->get(Index).key))
				return Index;
			if (Index + 1 < associative_arr->capacity)
				Index++;
			else
				Index = 0;
		}
	}
	return -1;
}
//--------------------------------------------------------//  main functions
void insert_pair(std::string key, std::string value, associative_array* associative_arr)
{
	int Index = hash(key, associative_arr->capacity);
	if (associative_arr->arr->get(Index).key.size() != 0)
	{
		while (associative_arr->arr->get(Index).key.size() != 0)
		{
			/*if (str_compare(key, associative_arr->arr->get(Index).key))
				return;
			else*/ if (Index + 1 < associative_arr->capacity)
				Index++;
			else
				Index = 0;
		}
	}
	ArrayElement* ArrElement = new ArrayElement;
	ArrElement->key = key;
	ArrElement->value = value;
	associative_arr->arr->set(Index, *ArrElement);
	associative_arr->size++;

	if (associative_arr->size >= associative_arr->capacity / 2)
	{
		Array<ArrayElement>* arr = new Array<ArrayElement>(associative_arr->capacity * 2);
		for (int i = 0; i < associative_arr->capacity; i++)
		{
			if (associative_arr->arr->get(i).key.size() != 0)
			{
				ArrayElement* arr_el = new ArrayElement;
				arr_el->key = associative_arr->arr->get(i).key;
				arr_el->value = associative_arr->arr->get(i).value;
				arr->set(hash(associative_arr->arr->get(i).key, associative_arr->capacity * 2), *arr_el);
			}
		}
		associative_arr->arr = arr;
		associative_arr->capacity *= 2;
	}
}

std::string find(std::string key, associative_array* associative_arr)
{
	int Index = find_index(key, associative_arr);
	if (Index == -1)
		return "";
	else
		return associative_arr->arr->get(Index).value;
}

void delete_pair(std::string key, associative_array* associative_arr)
{
	int Del_Index = find_index(key, associative_arr);
	if (Del_Index == -1) return;
	associative_arr->size--;
	int Hash = hash(associative_arr->arr->get(Del_Index).key, associative_arr->capacity);
	ArrayElement* empty = new ArrayElement;
	empty->key = "";
	empty->value = "";
	int Move_Index = Del_Index;
	do {
		if (Move_Index + 1 < associative_arr->capacity)
			Move_Index++;
		else
			Move_Index = 0;
	} while (associative_arr->arr->get(Move_Index).key.size() != 0 && hash(associative_arr->arr->get(Move_Index).key, associative_arr->capacity) > Hash);
	if (associative_arr->arr->get(Move_Index).key.size() != 0)
	{
		ArrayElement* arr_el = new ArrayElement;
		arr_el->key = associative_arr->arr->get(Move_Index).key;
		arr_el->value = associative_arr->arr->get(Move_Index).value;
		associative_arr->arr->set(Del_Index, *arr_el);
		associative_arr->arr->set(Move_Index, *empty);
	}
	else
		associative_arr->arr->set(Del_Index, *empty);
}