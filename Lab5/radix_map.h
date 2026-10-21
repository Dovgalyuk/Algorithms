#ifndef RADIX_MAP_H
#define RADIX_MAP_H

#include <map>
#include <memory>
#include <iterator>
#include <cstddef>
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

    class const_iterator
    {
        struct Frame
        {
            const Node *node;
            Children::const_iterator child;
            size_t key_size;

            Frame(const Node *value, size_t size)
                : node(value), child(value->children.begin()), key_size(size) {}
        };

    public:
        typedef forward_iterator_tag iterator_category;
        typedef pair<string, string> value_type;
        typedef ptrdiff_t difference_type;
        typedef const value_type *pointer;
        typedef const value_type &reference;

        const_iterator() : owner_(nullptr), finished_(true) {}

        reference operator*() const
        {
            return current_;
        }

        pointer operator->() const
        {
            return &current_;
        }

        const_iterator &operator++()
        {
            if (!finished_)
                next_value();
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator result = *this;
            ++(*this);
            return result;
        }

        bool operator==(const const_iterator &other) const
        {
            if (owner_ != other.owner_ || finished_ != other.finished_)
                return false;
            return finished_ || current_.first == other.current_.first;
        }

        bool operator!=(const const_iterator &other) const
        {
            return !(*this == other);
        }

    private:
        friend class RadixMap;

        const_iterator(const RadixMap *owner, const Node *root)
            : owner_(owner), finished_(false)
        {
            stack_.push_back(Frame(root, 0));
            if (root->has_value)
                current_ = make_pair(key_, root->value);
            else
                next_value();
        }

        explicit const_iterator(const RadixMap *owner)
            : owner_(owner), finished_(true) {}

        void next_value()
        {
            while (!stack_.empty())
            {
                Frame &frame = stack_.back();
                if (frame.child == frame.node->children.end())
                {
                    stack_.pop_back();
                    if (stack_.empty())
                    {
                        finished_ = true;
                        return;
                    }
                    key_.resize(stack_.back().key_size);
                    continue;
                }

                Children::const_iterator child = frame.child++;
                const Edge &edge = child->second;
                key_ += edge.label;
                const Node *node = edge.next.get();
                stack_.push_back(Frame(node, key_.size()));
                if (node->has_value)
                {
                    current_ = make_pair(key_, node->value);
                    return;
                }
            }
            finished_ = true;
        }

        const RadixMap *owner_;
        vector<Frame> stack_;
        string key_;
        value_type current_;
        bool finished_;
    };

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

    const_iterator begin() const
    {
        return const_iterator(this, &root_);
    }

    const_iterator end() const
    {
        return const_iterator(this);
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

    Node root_;
};

#endif
