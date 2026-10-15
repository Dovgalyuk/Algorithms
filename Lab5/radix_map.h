#ifndef RADIX_MAP_H
#define RADIX_MAP_H

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class RadixMap
{
    struct Node;

    struct Edge
    {
        string label;
        unique_ptr<Node> next;

        Edge(const string &text, unique_ptr<Node> node)
            : label(text), next(move(node)) {}
    };

    typedef map<char, Edge> Children;

    struct Node
    {
        bool has_value = false;
        string value;
        Children children;
    };

public:
    typedef vector<pair<string, string>> Entries;
    typedef Entries::const_iterator const_iterator;

    void insert(const string &key, const string &value)
    {
        insert(root_, key, value);
    }

    const string *find(const string &key) const
    {
        const Node *node = &root_;
        size_t position = 0;
        while (position < key.size())
        {
            Children::const_iterator it = node->children.find(key[position]);
            if (it == node->children.end())
                return nullptr;

            const Edge &edge = it->second;
            if (key.compare(position, edge.label.size(), edge.label) != 0)
                return nullptr;

            position += edge.label.size();
            node = edge.next.get();
        }
        return node->has_value ? &node->value : nullptr;
    }

    bool erase(const string &key)
    {
        return erase(root_, key);
    }

    Entries entries() const
    {
        Entries result;
        collect(root_, "", result);
        return result;
    }

    const_iterator begin() const
    {
        cache_ = entries();
        return cache_.begin();
    }

    const_iterator end() const
    {
        return cache_.end();
    }

private:
    static size_t common_prefix(const string &left, const string &right)
    {
        size_t length = 0;
        while (length < left.size() && length < right.size()
               && left[length] == right[length])
            ++length;
        return length;
    }

    static void insert(Node &node, const string &key, const string &value)
    {
        if (key.empty())
        {
            node.value = value;
            node.has_value = true;
            return;
        }

        Children::iterator it = node.children.find(key[0]);
        if (it == node.children.end())
        {
            unique_ptr<Node> leaf(new Node());
            leaf->value = value;
            leaf->has_value = true;
            node.children.emplace(key[0], Edge(key, move(leaf)));
            return;
        }

        Edge &edge = it->second;
        size_t prefix = common_prefix(edge.label, key);
        if (prefix == edge.label.size())
        {
            insert(*edge.next, key.substr(prefix), value);
            return;
        }

        string old_suffix = edge.label.substr(prefix);
        unique_ptr<Node> middle(new Node());
        middle->children.emplace(old_suffix[0], Edge(old_suffix, move(edge.next)));
        edge.label.resize(prefix);
        edge.next = move(middle);

        if (prefix == key.size())
        {
            edge.next->value = value;
            edge.next->has_value = true;
        }
        else
        {
            string new_suffix = key.substr(prefix);
            unique_ptr<Node> leaf(new Node());
            leaf->value = value;
            leaf->has_value = true;
            edge.next->children.emplace(new_suffix[0], Edge(new_suffix, move(leaf)));
        }
    }

    static bool erase(Node &node, const string &key)
    {
        if (key.empty())
        {
            if (!node.has_value)
                return false;
            node.has_value = false;
            node.value.clear();
            return true;
        }

        Children::iterator it = node.children.find(key[0]);
        if (it == node.children.end())
            return false;

        Edge &edge = it->second;
        if (key.compare(0, edge.label.size(), edge.label) != 0)
            return false;
        if (!erase(*edge.next, key.substr(edge.label.size())))
            return false;

        if (!edge.next->has_value && edge.next->children.empty())
            node.children.erase(it);
        else if (!edge.next->has_value && edge.next->children.size() == 1)
        {
            Children::iterator only = edge.next->children.begin();
            edge.label += only->second.label;
            edge.next = move(only->second.next);
        }
        return true;
    }

    static void collect(const Node &node, const string &prefix, Entries &result)
    {
        if (node.has_value)
            result.push_back(make_pair(prefix, node.value));
        for (Children::const_iterator it = node.children.begin();
             it != node.children.end(); ++it)
            collect(*it->second.next, prefix + it->second.label, result);
    }

    Node root_;
    mutable Entries cache_;
};

#endif
