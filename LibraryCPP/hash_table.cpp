#include <string>
#include <stdexcept>
#include "my_hash.h"
#include "hash_table.h"

HashTable::HashTable() : size(1024), count(0), load_factor(0.7)
{
	array = new HashTable::KeyValue[size];
	fill(array, size);
}

HashTable::~HashTable()
{
	delete[] array;
}

void HashTable::insert(std::string key, std::string value)
{	
	if (check_key(key))
		throw std::invalid_argument("The key already exists");

	if (((count+1)/size) >= load_factor) {
		rehash(size * 2);
	} 

	insert(key, value, array, size);
	count++;
}

std::string HashTable::get(std::string key)
{
	size_t index = find_index(key, array, size, false);
	if (!check_key(index)) 
		throw std::invalid_argument("This key does not exist");

	return array[index].value;
}

void HashTable::set(std::string key, std::string value)
{
	size_t index = find_index(key, array, size, false);
	if (check_key(index))
		array[index].value = value;
	else
		insert(key, value);
}

bool HashTable::check_key(std::string key)
{
	return check_key(find_index(key, array, size, false));
}

bool HashTable::check_key(size_t index)
{
	return array[index].type == HashTable::Type::Value;
}

void HashTable::remove(std::string key)
{
	size_t index = find_index(key, array, size, false);
	if (!check_key(index))
		throw std::invalid_argument("Cannot remove: the key does not exist");

	array[index].type = HashTable::Type::Delete;
	count--;
}

void HashTable::fill(HashTable::KeyValue *array, size_t size)
{
	for (size_t ind = 0; ind < size; ind++)
		array[ind] = HashTable::KeyValue();
}

void HashTable::rehash(size_t new_size)
{
	if ((new_size & (new_size - 1)) and (new_size >= 2))
		throw std::invalid_argument("New size should be a power of 2 and not less than 2");
	if ((new_size < count) or ((count / new_size) >= load_factor))
		throw std::invalid_argument("The new size is too small for the current number of elements");

	HashTable::KeyValue *new_array = new HashTable::KeyValue[new_size];
	fill(new_array, new_size);
	size_t cnt = 0;
	for (size_t ind = 0; (ind < size) && (cnt < count); ind++)
		if (array[ind].type == HashTable::Type::Value) {
			insert(array[ind].key, array[ind].value, new_array, new_size);
			cnt++;
		}

	delete[] array;

	size = new_size;
	array = new_array;
}

size_t HashTable::get_start_index(std::string key, size_t size)
{
	return my_hash1(key) % size;
}

size_t HashTable::get_step(std::string key, size_t size)
{
	return 1 + 2 * (my_hash2(key) % (size / 2));
}

size_t HashTable::find_index(std::string key, HashTable::KeyValue *array, size_t size, bool insert_mode)
{
	size_t index = get_start_index(key, size);
	size_t step = get_step(key, size);
	size_t k = 0;

	do {
		size_t current_index = (index + k * step) % size;
		HashTable::KeyValue tmp = array[current_index];
		if (insert_mode) {
			if ((tmp.type == HashTable::Type::None) or (tmp.type == HashTable::Type::Delete))
				return current_index;
		}
		else {
			if ((tmp.type == HashTable::Type::None) or ((tmp.type == HashTable::Type::Value) and ((tmp.key) == key)))
				return current_index;
		}

		k++;
	} while (index != (index + k * step) % size);


	// This is only possible if the function is looking for the index of a non-existent key.
	// And all elements in the array are of either delete or value type, i.e. there is no None type.
	for (size_t ind = 0; ind < size; ind++) {
		if (array[ind].type != HashTable::Type::Value) {
			index = ind; 
			break;
		}
	}
	return index;	
}
	
void HashTable::insert(std::string key, std::string value, HashTable::KeyValue *array, size_t size)
{
	size_t index = find_index(key, array, size, true);
	array[index].key = key;
	array[index].value = value;
	array[index].type = HashTable::Type::Value;
}