#ifndef STRING_MAP_TEMPLATE_H
#define STRING_MAP_TEMPLATE_H

#include <iterator>
#include <memory>
#include <type_traits>

#include "associative_array.h"
#include "vector.h"

template <typename Key, typename Value>
class AvlTreeMap : public AssociativeArray<Key, Value>
{
    using Base = AssociativeArray<Key, Value>;

public:
    using Order = typename Base::Order;
    using BaseIterator = typename Base::Iterator;

    struct Entry
    {
        const Key key;
        Value value;
        Entry(const Key &initialKey, const Value &initialValue) : key(initialKey), value(initialValue) {}
    };

private:
    struct Node : Entry
    {
        Node *left = nullptr;
        Node *right = nullptr;
        int height = 1;
        Node(const Key &initialKey, const Value &initialValue) : Entry(initialKey, initialValue) {}
    };

public:
    template <bool IsConst, bool IsReverse>
    class Iter
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Entry;
        using difference_type = std::ptrdiff_t;
        using pointer = typename std::conditional<IsConst, const Entry *, Entry *>::type;
        using reference = typename std::conditional<IsConst, const Entry &, Entry &>::type;

        Iter() = default;

        template <bool IsConstSource = IsConst, typename = typename std::enable_if<IsConstSource>::type>
        Iter(const Iter<false, IsReverse> &other) : nodePath(other.nodePath) {}

        reference operator*() const { return *currentNode(); }
        pointer operator->() const { return currentNode(); }

        Iter &operator++()
        {
            Node *current = currentNode();
            nodePath.pop();

            if (!IsReverse)
            {
                if (current->right)
                {
                    pushPathToFirst(current->right, false);
                }
                else
                {
                    while (!nodePath.empty() && nodePath.back()->right == current)
                    {
                        current = nodePath.back();
                        nodePath.pop();
                    }
                }
            }
            else
            {
                if (current->left)
                {
                    pushPathToFirst(current->left, true);
                }
                else
                {
                    while (!nodePath.empty() && nodePath.back()->left == current)
                    {
                        current = nodePath.back();
                        nodePath.pop();
                    }
                }
            }

            return *this;
        }

        Iter operator++(int)
        {
            Iter previousState = *this;
            ++*this;
            return previousState;
        }

        friend bool operator==(const Iter &first, const Iter &second)
        {
            if (first.nodePath.size() == 0 || second.nodePath.size() == 0)
                return (first.nodePath.size() == 0) == (second.nodePath.size() == 0);
            return first.currentNode() == second.currentNode();
        }
        friend bool operator!=(const Iter &first, const Iter &second) { return !(first == second); }

    private:
        friend class AvlTreeMap;
        template <bool, bool>
        friend class Iter;

        explicit Iter(Node *root) { pushPathToFirst(root, IsReverse); }

        Node *currentNode() const { return nodePath[nodePath.size() - 1]; }

        void pushPathToFirst(Node *node, bool reverseDirection)
        {
            while (node)
            {
                nodePath.push(node);
                node = reverseDirection ? node->right : node->left;
            }
        }

        Vector<Node *> nodePath;
    };

    using iterator = Iter<false, false>;
    using const_iterator = Iter<true, false>;
    using reverse_iterator = Iter<false, true>;
    using const_reverse_iterator = Iter<true, true>;

    AvlTreeMap() = default;

    AvlTreeMap(const AvlTreeMap &other) : Base(), rootNode(cloneSubtree(other.rootNode)), elementCount(other.elementCount) {}

    AvlTreeMap(AvlTreeMap &&other) noexcept : Base(), rootNode(other.rootNode), elementCount(other.elementCount)
    {
        other.rootNode = nullptr;
        other.elementCount = 0;
    }

    AvlTreeMap &operator=(AvlTreeMap other) noexcept
    {
        Node *oldRoot = rootNode;
        std::size_t oldSize = elementCount;
        rootNode = other.rootNode;
        elementCount = other.elementCount;
        other.rootNode = oldRoot;
        other.elementCount = oldSize;
        return *this;
    }
    ~AvlTreeMap() override { destroySubtree(rootNode); }

    bool insert(const Key &key, const Value &value) override
    {
        bool keyWasNew = false;
        rootNode = insertIntoSubtree(rootNode, key, value, keyWasNew);
        if (keyWasNew)
            ++elementCount;
        return keyWasNew;
    }

    Value *find(const Key &key) override
    {
        return const_cast<Value *>(static_cast<const AvlTreeMap &>(*this).find(key));
    }

    const Value *find(const Key &key) const override
    {
        const Node *current = rootNode;
        while (current)
        {
            if (key < current->key)
                current = current->left;
            else if (current->key < key)
            {

                current = current->right;
            }
            else
            {
                return &current->value;
            }
        }
        return nullptr;
    }

    bool erase(const Key &key) override
    {
        bool keyWasRemoved = false;
        rootNode = eraseFromSubtree(rootNode, key, keyWasRemoved);
        if (keyWasRemoved)
            --elementCount;
        return keyWasRemoved;
    }

    bool contains(const Key &key) const override { return find(key) != nullptr; }
    std::size_t size() const override { return elementCount; }
    bool empty() const override { return elementCount == 0; }
    void clear() override
    {
        destroySubtree(rootNode);
        rootNode = nullptr;
        elementCount = 0;
    }

    int height() const
    {
        return subtreeHeight(rootNode);
    }

    bool validate() const
    {
        const Key *noLowerLimit = nullptr;
        const Key *noUpperLimit = nullptr;
        return validateSubtree(rootNode, noLowerLimit, noUpperLimit) >= 0;
    }

    std::unique_ptr<BaseIterator> createIterator(Order order = Order::Ascending) const override
    {
        if (order == Order::Ascending)
            return std::unique_ptr<BaseIterator>(new PolymorphicIterator<false>(rootNode));
        return std::unique_ptr<BaseIterator>(new PolymorphicIterator<true>(rootNode));
    }

    iterator begin() { return iterator(rootNode); }
    iterator end() { return iterator(); }
    const_iterator begin() const { return const_iterator(rootNode); }
    const_iterator end() const { return const_iterator(); }
    const_iterator cbegin() const { return begin(); }
    const_iterator cend() const { return end(); }

    reverse_iterator rbegin() { return reverse_iterator(rootNode); }
    reverse_iterator rend() { return reverse_iterator(); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(rootNode); }
    const_reverse_iterator rend() const { return const_reverse_iterator(); }

private:
    template <bool IsReverse>
    class PolymorphicIterator : public BaseIterator
    {
    public:
        explicit PolymorphicIterator(Node *root) : innerIterator(root) {}
        bool valid() const override { return innerIterator != Iter<true, IsReverse>(); }
        void next() override { ++innerIterator; }
        const Key &key() const override { return innerIterator->key; }
        const Value &value() const override { return innerIterator->value; }

    private:
        Iter<true, IsReverse> innerIterator;
    };

    Node *rootNode = nullptr;
    std::size_t elementCount = 0;

    static int largerOf(int first, int second) { return first > second ? first : second; }
    static int subtreeHeight(const Node *node) { return node ? node->height : 0; }
    static void updateHeight(Node *node) { node->height = 1 + largerOf(subtreeHeight(node->left), subtreeHeight(node->right)); }

    static int validateSubtree(const Node *node, const Key *minKey, const Key *maxKey)
    {
        if (!node)
        {
            return 0;
        }
        if (minKey && !(*minKey < node->key))
        {
            return -1;
        }
        if (maxKey && !(node->key < *maxKey))
            return -1;

        int leftHeight = validateSubtree(node->left, minKey, &node->key);
        if (leftHeight < 0)
            return -1;
        int rightHeight = validateSubtree(node->right, &node->key, maxKey);
        if (rightHeight < 0)
            return -1;

        int balanceDifference = leftHeight - rightHeight;
        if (balanceDifference > 1 || balanceDifference < -1)
            return -1;

        int expectedHeight = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
        if (node->height != expectedHeight)
            return -1;
        return expectedHeight;
    }

    static Node *rotateRight(Node *pivotNode)
    {
        Node *newRoot = pivotNode->left;
        pivotNode->left = newRoot->right;
        newRoot->right = pivotNode;
        updateHeight(pivotNode);
        updateHeight(newRoot);
        return newRoot;
    }
    static Node *rotateLeft(Node *pivotNode)
    {
        Node *newRoot = pivotNode->right;
        pivotNode->right = newRoot->left;
        newRoot->left = pivotNode;
        updateHeight(pivotNode);
        updateHeight(newRoot);
        return newRoot;
    }
    static Node *rebalance(Node *node)
    {
        updateHeight(node);
        int balanceFactor = subtreeHeight(node->left) - subtreeHeight(node->right);
        if (balanceFactor > 1)
        {
            if (subtreeHeight(node->left->left) < subtreeHeight(node->left->right))
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balanceFactor < -1)
        {
            if (subtreeHeight(node->right->right) < subtreeHeight(node->right->left))
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    static Node *insertIntoSubtree(Node *node, const Key &key, const Value &value, bool &keyWasNew)
    {
        if (!node)
        {
            keyWasNew = true;
            return new Node(key, value);
        }
        if (key < node->key)
        {
            node->left = insertIntoSubtree(node->left, key, value, keyWasNew);
        }
        else if (node->key < key)
        {
            node->right = insertIntoSubtree(node->right, key, value, keyWasNew);
        }
        else
        {
            node->value = value;
            return node;
        }
        return rebalance(node);
    }

    static Node *detachMinimumNode(Node *node, Node *&minimumNode)
    {
        if (!node->left)
        {
            minimumNode = node;
            return node->right;
        }
        node->left = detachMinimumNode(node->left, minimumNode);
        return rebalance(node);
    }

    static Node *eraseFromSubtree(Node *node, const Key &key, bool &keyWasRemoved)
    {
        if (!node)
        {
            return nullptr;
        }
        if (key < node->key)
        {
            node->left = eraseFromSubtree(node->left, key, keyWasRemoved);
        }
        else if (node->key < key)
        {
            node->right = eraseFromSubtree(node->right, key, keyWasRemoved);
        }
        else
        {
            keyWasRemoved = true;
            Node *leftSubtree = node->left;
            Node *rightSubtree = node->right;
            delete node;
            if (!rightSubtree)
            {
                return leftSubtree;
            }
            Node *successorNode = nullptr;
            rightSubtree = detachMinimumNode(rightSubtree, successorNode);
            successorNode->left = leftSubtree;
            successorNode->right = rightSubtree;
            return rebalance(successorNode);
        }
        return rebalance(node);
    }

    static Node *cloneSubtree(const Node *source)
    {
        if (!source)
        {
            return nullptr;
        }
        Node *copy = new Node(source->key, source->value);
        copy->height = source->height;
        copy->left = cloneSubtree(source->left);
        copy->right = cloneSubtree(source->right);
        return copy;
    }

    static void destroySubtree(Node *node)
    {
        if (!node)
        {
            return;
        }
        destroySubtree(node->left);
        destroySubtree(node->right);
        delete node;
    }
};

#endif