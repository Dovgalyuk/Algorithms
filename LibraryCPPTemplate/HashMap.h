#include <string>
#include <stdexcept>
#include <array>
#include <vector>
#include "IContainer.h"

using std::string;

struct Pair
{
	string key;
	string value;
};


class HashMap : IContainer<string>
{
public:
	HashMap(size_t capacity): _capacity(capacity)
	{
		_nodes.resize(capacity);
	}

	HashMap(): HashMap(10){ }

	string Add(string key, string value) override
	{
		size_t index = get_index(key);

		for (index; index < _nodes.size(); index++)
		{
			Node* node = &_nodes[index];
			if (node->status != NodeStatus::Full)
			{
				node->pair.key = key;
				node->pair.value = value;

				node->status = NodeStatus::Full;
				return key;
			}

			if (index == _nodes.size() - 1)
			{
				rehash();
			}
		}

	}

	string Remove(string key) override
	{
		size_t index = get_index(key);

		for (index; index < _nodes.size(); index++)
		{
			Node* node = &_nodes[index];
			if (node->pair.key == key && node->status == NodeStatus::Empty)
			{
				node->pair.key = "";
				node->pair.value = "";

				node->status = NodeStatus::Erased;
				return "";
			}
		}

		throw std::logic_error("No proposed key in Delete() of hash_map");
	}

	string Find(string key) override
	{
		size_t index = get_index(key);

		for (index; index < _nodes.size(); index++)
		{
			Node node = _nodes[index];
			if (node.pair.key == key && node.status == NodeStatus::Full)
			{
				return node.pair.value;
			}
		}

		throw std::logic_error("No proposed key in Find() of hash_map");
	}
	
private:
	enum class NodeStatus
	{
		Full, Empty, Erased
	};
	
	struct Node
	{
		Pair pair;
		NodeStatus status = NodeStatus::Empty;
	};
	
	size_t get_index(string key) const
	{
		return (str_hash(key) *22543) % _capacity;
	}

	void rehash()
	{
		auto old_nodes = _nodes;

		_nodes.clear();
		_capacity *= 2;
		_nodes.resize(_capacity);
		
		for (int i = 0; i < _capacity / 2; i++)
		{
			if (old_nodes[i].status == NodeStatus::Full)
			{
				Add(old_nodes[i].pair.key, old_nodes[i].pair.value);
			}
		}
	}
	
	size_t _capacity;

	std::vector<Node> _nodes;
	std::hash<string> str_hash = std::hash<string>{};
};