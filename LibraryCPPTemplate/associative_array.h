#ifndef ASSOCIATIVE_ARRAY_INTERFACE_H
#define ASSOCIATIVE_ARRAY_INTERFACE_H

#include <memory>

template <typename Key, typename Value>
class AssociativeArray
{
public:
    enum class Order
    {
        Ascending,
        Descending
    };
    class Iterator
    {
    public:
        virtual ~Iterator() = default;

        virtual bool valid() const = 0;
        virtual void next() = 0;
        virtual const Key &key() const = 0;
        virtual const Value &value() const = 0;
    };

    virtual ~AssociativeArray() = default;

    virtual bool insert(const Key &key, const Value &value) = 0;

    virtual Value *find(const Key &key) = 0;
    virtual const Value *find(const Key &key) const = 0;

    virtual bool erase(const Key &key) = 0;

    virtual bool contains(const Key &key) const = 0;
    virtual std::size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual void clear() = 0;

    virtual std::unique_ptr<Iterator> createIterator(Order order = Order::Ascending) const = 0;

protected:
    AssociativeArray() = default;
};

#endif