#include "associative_array.h"
#include "../LibraryCPPTemplate/array.h" 
#include<string>

struct ArrayElement
{
	std::string key;
	std::string value;
	bool deleted = false;
};

struct associative_array
{
	int capacity = 23;
	int size = 0;
	int deleted_el = 0;
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
	unsigned long long p = 1;
	for (int i = 0; i < str.size(); i++)
	{
		sum += (str[i] * p) % capacity;
		p *= 31;
	}
	return sum % capacity;
}

int hash2(std::string str, int capacity)  //double hash
{
	int sum = 0;
	unsigned long long p = 1;
	for (int i = str.size() - 1; i >= 0; i--)
	{
		sum += (str[i] * p) % capacity;
		p *= 23;
	}
	int result = sum % capacity;
	if (result % 2 == 0)
		return result + 1;
	else return result;
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
	int final_index = Index;
	if (associative_arr->arr->get(final_index).key.size() != 0)
	{
		int Index2 = hash2(key, associative_arr->capacity);
		int j = 0;
		final_index = (Index + Index2 * j) % associative_arr->capacity;
		while (associative_arr->arr->get(final_index).deleted == false && associative_arr->arr->get(final_index).key.size() != 0)
		{
			if (str_compare(key, associative_arr->arr->get(final_index).key))
				return final_index;
			j++;
			final_index = (Index + Index2 * j) % associative_arr->capacity;
		}
	}
	return -1;
}
//--------------------------------------------------------//  main functions
void insert_pair(std::string key, std::string value, associative_array* associative_arr)
{
	int capacity = associative_arr->capacity;
	int Index = hash(key, capacity);
	int final_index = Index;
	if (associative_arr->arr->get(final_index).key.size() != 0 && associative_arr->arr->get(final_index).deleted == false)
	{
		int Index2 = hash2(key, capacity);
		int j = 1;
		final_index = (Index + Index2 * j) % capacity;
		while (associative_arr->arr->get(final_index).key.size() != 0 && associative_arr->arr->get(final_index).deleted == false)
		{
			j++;
			final_index = (Index + Index2 * j) % capacity;
		}
	}
	ArrayElement* ArrElement = new ArrayElement;
	ArrElement->key = key;
	ArrElement->value = value;
	associative_arr->arr->set(final_index, *ArrElement);
	associative_arr->size++;

	if (associative_arr->size >= capacity / 2)
	{
		Array<ArrayElement>* arr = new Array<ArrayElement>(capacity * 2);
		for (int i = 0; i < capacity; i++)
		{
			if (associative_arr->arr->get(i).key.size() != 0 && associative_arr->arr->get(i).deleted == false)
			{
				int Index = hash(associative_arr->arr->get(i).key, capacity * 2);
				int final_index = Index;
				if (arr->get(final_index).key.size() != 0)
				{
					int Index2 = hash2(associative_arr->arr->get(i).key, capacity * 2);
					int j = 1;
					final_index = (Index + Index2 * j) % (capacity * 2);
					while (arr->get(final_index).key.size() != 0)
					{
						j++;
						final_index = (Index + Index2 * j) % (capacity * 2);
					}
				}
				arr->set(final_index, associative_arr->arr->get(i));
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
	associative_arr->deleted_el++;
	ArrayElement* arr_el = new ArrayElement;
	arr_el->key = associative_arr->arr->get(Del_Index).key;
	arr_el->value = associative_arr->arr->get(Del_Index).value;
	arr_el->deleted = true;
	associative_arr->arr->set(Del_Index, *arr_el);
}