#include <fstream>
#include "array.h"
#include "stack.h"
#include <iostream>

void merge(Array& arr, int left, int mid, int right)
{
    size_t temp_size = right - left + 1;
    Array temp(temp_size);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
    {
        if (arr.get(i) <= arr.get(j))
        {
            temp.set(k++, arr.get(i++));
        }
        else
        {
            temp.set(k++, arr.get(j++));
        }
    }

    while (i <= mid)
    {
        temp.set(k++, arr.get(i++));
    }

    while (j <= right)
    {
        temp.set(k++, arr.get(j++));
    }

    for (int p = 0; p < static_cast<int>(temp_size); p++)
    {
        arr.set(left + p, temp.get(p));
    }
}

void mergeSort(Array& arr)
{
    int n = static_cast<int>(arr.size());
    if (n <= 1) return;

    Stack stack;
    stack.push(0);
    stack.push(n - 1);
    stack.push(0); // 0=sort

    while (!stack.empty())
    {
        int type = stack.get();
        stack.pop();
        int right = stack.get();
        stack.pop();

        if (type == 0)
        {
            int left = stack.get();
            stack.pop();
            if (left >= right) continue;
            int mid = left + (right - left) / 2;
            stack.push(left);
            stack.push(mid);
            stack.push(right);
            stack.push(1); // 1=merge
            stack.push(mid + 1);
            stack.push(right);
            stack.push(0);
            stack.push(left);
            stack.push(mid);
            stack.push(0);
        }
        else
        {
            int mid = stack.get();
            stack.pop();
            int left = stack.get();
            stack.pop();
            merge(arr, left, mid, right);
        }
    }
}


int main(int argc, char** argv)
{
    if (argc < 2) return 1;

    std::ifstream in(argv[1]);
    if (!in) return 1;

    size_t count = 0;
    int num;
    while (in >> num)
    {
        count++;
    }
    in.clear();
    in.seekg(0);

    Array arr(count);
    size_t index = 0;
    while (in >> num)
    {
        arr.set(index++, num);
    }

    mergeSort(arr);

    for (size_t i = 0; i < arr.size(); i++)
    {
        std::cout << arr.get(i) << " ";
    }

    return 0;
}
