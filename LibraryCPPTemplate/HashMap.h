#include <string>
#include <stdexcept>
#include <array>
#include <vector>
#include <functional>
#include "IContainer.h"

using std::string;


class HashMap : IContainer<string>
{
public:
    HashMap(size_t capacity) : _capacity(capacity)
    {
        _nodes.resize(capacity);
    }

    HashMap() : HashMap(10) { }

    ~HashMap() override = default;

    string Add(string key, string value) override
    {
        MyFunc condition = [](Node& node, string& key) {return node.status != NodeStatus::Full; };
        
        size_t index = find_index(key, condition);
        if (index == -1)
        {
            rehash();
            index = find_index(key, condition);
        }

        Node* node = &_nodes[index];
        node->key = key;
        node->value = value;

        node->status = NodeStatus::Full;
        return key;
    }

    string Remove(string key) override
    {
        MyFunc condition = [](Node& node, string& key) {return node.key == key && node.status == NodeStatus::Full; };
        
        size_t index = find_index(key, condition);
        if (index == -1) throw std::logic_error("No proposed key in Delete() of hash_map");

        Node* node = &_nodes[index];
        node->key = "";
        node->value = "";

        node->status = NodeStatus::Erased;
        return "";
    }

    string Find(string key) override
    {
        MyFunc condition = [](Node& node, string& key) {return node.key == key && node.status == NodeStatus::Full; };

        size_t index = find_index(key, condition);
        if (index == -1) throw std::logic_error("No proposed key in Find() of hash_map");

        return _nodes[index].value;
    }

private:
    enum class NodeStatus
    {
        Full, Empty, Erased
    };

    struct Node
    {
        string key;
        string value;
        NodeStatus status = NodeStatus::Empty;
    };

    typedef std::function<bool(Node&, string&)> MyFunc;

    size_t find_index(string& key, MyFunc& condition)
    {
        size_t index = get_index(key);

        size_t indexZ = do_circle(condition, key, index, _nodes.size());
        if (indexZ == -1)
        {
            indexZ = do_circle(condition, key, 0, index);
        }

        return indexZ;
    }
	
    size_t get_index(const string key) const
    {
        return (str_hash(key) * 22543) % _capacity;
    }

    size_t do_circle(MyFunc& condition, string& key, size_t index, size_t end) // another 0.001 boost
    {
        for (index; index < end; index++)
        {
            Node& node = _nodes[index];
            if (condition(node, key)) return index;
            if (node.status == NodeStatus::Empty) return -1;
        }
        return -1;
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
                Add(old_nodes[i].key, old_nodes[i].value);
            }
        }
    }

    size_t _capacity;
    std::vector<Node> _nodes;
    std::hash<string> str_hash = std::hash<string>{};
};