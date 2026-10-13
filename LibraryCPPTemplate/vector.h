#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <memory>
#include <exception>

template <typename Data>
class Vector
{
public:
    Vector() = default;

    explicit Vector(size_t new_cap) : Vector()
    {
        if (new_cap != 0)
        {
            resize(new_cap);
        }
    }

    Vector(const Vector &a) : vec(nullptr), len(0), cap(0)
    {
        if (a.len > 0)
        {
            vec = allocator.allocate(a.size());
            cap = a.size();

            try
            {
                for (; len < a.size(); len++)
                {
                    allocator.construct(&vec[len], a.vec[len]);
                }
            }

            catch (...)
            {
                for (size_t i = 0; i < len; i++)
                {
                    allocator.destroy(&vec[i]);
                }
                allocator.deallocate(vec, cap);
                throw;
            }
        }
    }

    Vector &operator=(const Vector &a)
    {
        if (this != &a)
        {
            Vector tmp(a);

            Data *t_vec = vec;
            size_t t_len = len;
            size_t t_cap = cap;

            vec = tmp.vec;
            len = tmp.len;
            cap = tmp.cap;

            tmp.vec = t_vec;
            tmp.len = t_len;
            tmp.cap = t_cap;
        }
        return *this;
    }

    ~Vector()
    {
        for (size_t i = 0; i < len; i++)
        {
            allocator.destroy(&vec[i]);
        }

        len = 0;

        if (vec)
        {
            allocator.deallocate(vec, cap);
        }
        cap = 0;
    }

    void add(size_t index, const Data &value)
    {
        if (index > len)
        {
            throw std::out_of_range("vector subscript out of range");
        }

        if (len == cap)
        {
            grow_buffer(1);
        }

        if (index == len)
        {
            allocator.construct(&vec[len], value);
        }
        else
        {
            allocator.construct(&vec[len], static_cast<Data &&>(vec[len - 1]));

            for (size_t i = len - 1; i > index; i--)
            {
                vec[i] = static_cast<Data &&>(vec[i - 1]);
            }
            vec[index] = value;
        }
        len++;
    }

    void insert(const Data &value)
    {
        add(0, value);
    }

    void push(const Data &value)
    {
        add(len, value);
    }

    void remove(size_t index)
    {
        if (index >= len)
        {
            throw std::out_of_range("vector subscript out of range");
        }

        for (size_t i = index; i < len - 1; i++)
        {
            vec[i] = static_cast<Data &&>(vec[i + 1]);
        }
        allocator.destroy(&vec[len - 1]);
        len--;
    }

    void pop()
    {
        if (len == 0)
        {
            throw std::out_of_range("vector subscript out of range");
        }
        remove(len - 1);
    }

    void removeFirst()
    {
        if (len == 0)
        {
            throw std::out_of_range("vector subscript out of range");
        }
        remove(0);
    }

    const Data &get(size_t index) const
    {
        if (index >= len)
        {
            throw std::out_of_range("vector subscript out of range");
        }
        return vec[index];
    }

    const Data &operator[](size_t index) const
    {
        return vec[index];
    }

    void set(size_t index, const Data &value)
    {
        if (index >= len)
        {
            throw std::out_of_range("vector subscript out of range");
        }
        vec[index] = value;
    }

    Data &operator[](size_t index)
    {
        return vec[index];
    }

    size_t size() const
    {
        return len;
    }

    size_t capacity() const
    {
        return cap;
    }

    void resize(size_t new_size)
    {
        if (new_size < len)
        {
            for (size_t i = new_size; i < len; i++)
            {
                allocator.destroy(&vec[i]);
            }
            len = new_size;
            return;
        }
        if (new_size > len)
        {
            if (new_size > cap)
            {
                grow_buffer(new_size - len);
            }
            size_t count = len;
            try
            {
                for (; count < new_size; count++)
                {
                    allocator.construct(&vec[count]);
                }
            }
            catch (...)
            {
                for (size_t i = len; i < count; i++)
                {
                    allocator.destroy(&vec[i]);
                }
                throw;
            }
            len = new_size;
        }
    }

    void reserve(size_t new_cap)
    {
        if (new_cap > allocator.max_size())
        {
            throw std::length_error("too long");
        }
        else if (new_cap <= cap)
        {
            return;
        }

        Data *new_vec = allocator.allocate(new_cap);
        size_t count = 0;

        try
        {
            for (; count < len; count++)
            {
                allocator.construct(&new_vec[count], static_cast<Data &&>(vec[count]));
            }
        }
        catch (...)
        {
            for (size_t i = 0; i < count; i++)
            {
                allocator.destroy(&new_vec[i]);
            }
            allocator.deallocate(new_vec, new_cap);
            throw;
        }

        for (size_t i = 0; i < len; i++)
        {
            allocator.destroy(&vec[i]);
        }

        if (vec)
        {
            allocator.deallocate(vec, cap);
        }

        vec = new_vec;
        cap = new_cap;
    }

    void clear(){
        resize(0);
    }

public:
    using value_type = Data;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = Data &;
    using pointer = Data *;
    using const_pointer = const Data *;

    using iterator = Data *;
    using const_iterator = const Data *;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    iterator begin() noexcept
    {
        return vec;
    }

    const_iterator begin() const noexcept
    {
        return vec;
    }

    iterator end() noexcept
    {
        return vec + len;
    }

    const_iterator end() const noexcept
    {
        return vec + len;
    }

    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

private:
    Data *vec = nullptr;
    size_t len = 0;
    size_t cap = 0;
    std::allocator<Data> allocator;

private:
    void grow_buffer(size_t n)
    {
        if (cap == allocator.max_size() || n > allocator.max_size() - len)
        {
            throw std::length_error("too long");
        }
        size_t new_cap = cap;

        if (cap > allocator.max_size() / 2)
        {
            new_cap = allocator.max_size();
        }
        else
        {
            new_cap = cap + (cap < n ? n : cap);
        }

        reserve(new_cap);
    }
};

#endif
