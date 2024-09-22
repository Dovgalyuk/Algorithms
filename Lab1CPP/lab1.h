#include "array.h"
#include <unordered_map>
#include <vector>

Array *array_create_and_read(FILE *input)
{
    int n;
    (void)fscanf(input, "%d", &n);
    Array *arr = new Array(n);
    for (int i = 0; i < n; ++i)
    {
        int x;
        (void)fscanf(input, "%d", &x);
        arr->set(i, x);
    }
    return arr;
}

std::vector<Data> task1(Array *arr)
{
    std::vector<Data> ans;
    Data sum = 0;
    for (size_t i = 0; i < arr->size(); i++)
    {
        sum += arr->get(i);
    }

    double average = double(sum) / double(arr->size());
    for (size_t i = 0; i < arr->size(); i++)
    {
        if (double(arr->get(i)) < average)
        {
            ans.push_back(arr->get(i));
        }
    }
    return ans;
}
std::vector<Data> task2(Array *arr)
{
    std::vector<Data> ans;
    enum Status
    {
        NotExist = 0,
        Wrong = 1,
        Pass = 2
    };
    std::unordered_map<Data, Status> m;
    for (size_t i = 0; i < arr->size(); i++)
    {
        auto current = arr->get(i);
        for (size_t j = 0; j < i; j++)
        {
            auto subEl = arr->get(j);
            if (subEl == current)
            {
                m[subEl] = Wrong;
                m[current] = Wrong;
            }
            else
            {
                int max = subEl > current ? subEl : current;
                int min = subEl < current ? subEl : current;
                if (min!=0 && max % min == 0)//TODO division by zero?
                {
                    m[max] = Wrong;
                }
                else if (m[max] == NotExist)
                {
                    m[max] = Pass;
                }
            }
        }
    }

    for (auto const &val : m)
    {
        if (val.second == Pass)
        {
            ans.push_back(val.first);
        }
    }
    return ans;
}