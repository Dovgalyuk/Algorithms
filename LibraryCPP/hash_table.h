#ifndef HASH_TABLE
#define HASH_TABLE

#include <string>

class HashTable
{
public:
	enum class Type {
		None,
		Value,
		Delete
	};

	struct KeyValue {
		Type type;
		std::string key;
		std::string value;

		KeyValue() : type(Type::None) {};
		KeyValue(const std::string &key, const std::string &value) : type(Type::Value), key(key), value(value) {};
	};

	HashTable();

	~HashTable();

	void insert(const std::string &key, const std::string &value);

	std::string &get(const std::string &key);

	void set(const std::string &key, const std::string &value);

	bool check_key(const std::string &key);

	void remove(const std::string &key);

private:
	size_t size;
	size_t count;
	KeyValue *array;
	const float load_factor; 

	void fill(KeyValue *array, size_t size);

	void rehash(size_t new_size);

	bool check_key(size_t index);

	size_t get_start_index(const std::string &key, size_t size);

	size_t get_step(const std::string &key, size_t size);

	size_t find_index(const std::string &key, KeyValue *array, size_t size, bool insert_mode);
	
	void insert(const std::string &key, const std::string &value, KeyValue *array, size_t size);
};

#endif