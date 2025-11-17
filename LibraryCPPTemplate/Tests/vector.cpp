#include <iostream>
#include "vector.h"

typedef Vector<int> MyVector;

int main()
{
    MyVector vector;

    vector.resize(5);
    if (vector.size() != 5)
    {
        std::cout << "Invalid resize\n";
        return 1;
    }

    for (size_t i = 0 ; i < vector.size() ; ++i)
        vector.set(i, i);

    vector = vector;

    for (size_t i = 0 ; i < vector.size() ; ++i)
    {
        if (vector.get(i) != (int)i)
        {
            std::cout << "Invalid vector element " << i << "\n";
            return 1;
        }
    }

    vector.resize(10);
    if (vector.size() != 10)
    {
        std::cout << "Invalid resize\n";
        return 1;
    }

    std::cout << "Vector: ";
    for (size_t i = 0 ; i < vector.size() ; ++i)
        std::cout << vector.get(i) << " ";
    std::cout << "\n";

    vector.resize(3);
    if (vector.size() != 3)
    {
        std::cout << "Invalid resize\n";
        return 1;
    }

    for (size_t i = 0 ; i < vector.size() ; ++i)
    {
        if (vector.get(i) != (int)i)
        {
            std::cout << "Invalid vector element " << i << "\n";
            return 1;
        }
    }

    std::cout << "Vector: ";
    for (size_t i = 0 ; i < vector.size() ; ++i)
        std::cout << vector.get(i) << " ";
    std::cout << "\n";

    MyVector vector_pb;

    for(size_t i = 0; i < 10; ++i)
        vector_pb.push_back(i * 10);

    if(vector_pb.size() != 10)
    {
        std::cout << "Invalid push back\n";
        return 1; 
    }

    for(size_t i = 0; i < vector_pb.size(); ++i)
    {
        if(vector_pb.get(i) != (int)i * 10)
        {
            std::cout << "Invalid push_back value " << vector_pb[i] << "\n";
            return 1;
        }
    }
    
    MyVector index_vec = vector_pb;

    for(size_t i = 0; i < 5; ++i)
    {
        index_vec[i] = i;
    }

    for(size_t i = 0; i < index_vec.size(); ++i)
    {
        int exp = (i < 5) ? i : (int)i * 10;
        if(index_vec[i] != exp)
        {
            std::cout << "Invalid index op at i " << i;
            return 1;
        }
    }

    for (int i = 1 ; i <= 10000000 ; ++i)
    {
        vector.resize(i);
        vector.set(i - 1, i);
    }

    MyVector copy = vector;

    for (int i = 0 ; i < 10000000 ; ++i)
    {
        if (vector.get(i) != copy.get(i))
        {
            std::cout << "Invalid copy element " << i << "\n";
            return 1;
        }
    }

    long long sum = 0;
    for (int i = 0 ; i < 10000000 ; ++i)
        sum += vector.get(i);

    std::cout << sum << "\n";
}
