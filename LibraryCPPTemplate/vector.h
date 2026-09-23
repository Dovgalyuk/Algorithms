#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <memory>
#include <exception>

template <typename Data>
class Vector
{
public:
    Vector() : vec(nullptr), len(0), cap(0)
    {
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

    Data get(size_t index) const
    {
        if (index >= len)
        {
            throw std::out_of_range("vector subscript out of range");
        }
        return vec[index];
    }

    void set(size_t index, Data value)
    {
        if (index >= len)
        {
            throw std::out_of_range("vector subscript out of range");
        }
        vec[index] = value;
    }

    size_t size() const
    {
        return len;
    }

    void resize(size_t size)
    {
        if (size <= len)
        {
            for (size_t i = size; i < len; i++)
            {
                allocator.destroy(&vec[i]);
            }

            len = size;
        }

        else if (size > len)
        {
            if (size > cap)
            {
                size_t new_cap = cap == 0 ? size : cap * 2;
                if (new_cap < size)
                {
                    new_cap = size;
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

            size_t count = len;
            try
            {
                for (; count < size; count++)
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
            len = size;
        }
    }

private:
    Data *vec = nullptr;
    size_t len;
    size_t cap;
    std::allocator<Data> allocator;
};

#endif
