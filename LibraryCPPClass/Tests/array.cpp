#include <iostream>
#include "array.h"
#include <cstdlib>
#include <unordered_map>

void find_eql()
{
    int size = 0;
    std::cout<<"intput array size:";
    std::cin>>size;
    Array arr(size);
    std::unordered_map<int, int> mp;

    srand((unsigned)time(NULL));
    for(int i = 0; i < size; i++)
    {
        arr.set(i, rand() % 21 - 10);
        std::cout<<arr.get(i)<<"\n";
    }    

    for (int i = 0; i < int(arr.size()); i++)
    {
        mp[arr.get(i)]++;
    }

    for (auto x : mp)
    {
        if (x.second == 2)
        {
            std::cout <<"\n"<< "chislo " << x.first << " vstrechyaetsa "<<x.second<<" raza" << std::endl;
        }
    }
}

void func1()
{
    int size = 0;
    int k1 = 0;
    int k2 = 0;
    srand((unsigned)time(NULL));

    std::cout << "input array size: ";
    std::cin >> size;
    std::cout << "\n" << "input k1: ";
    std::cin >> k1;
    std::cout << "\n" << "input k2: ";
    std::cin >> k2;
    std::cout << std::endl;

    Array arr(size);

    for (int i = 0; i < int(arr.size()); i++)
    {
        arr.set(i, rand() % 21 - 10);
        if (arr.get(i) > 0)
        {
            std::cout << arr.get(i) << " - " << k1 << " = " << arr.get(i)-k1 << "\n";
        }
        else{
            std::cout << arr.get(i) << " - " << k2 << " = " << arr.get(i) - k2 << "\n";
        }
    }
}

int main()
{
    Array *arr = new Array(10);

    if (arr->size() != 10)
    {
        std::cout << "Invalid array size\n";
        return 1;
    }

    for (int i = 0 ; i < 10 ; ++i)
        arr->set(i, i * 2);

    Array copy(*arr);

    for (int i = 0 ; i < 10 ; ++i)
    {
        if (arr->get(i) != i * 2
            || copy.get(i) != i * 2)
        {
            std::cout << "Invalid array element " << i << "\n";
            return 1;
        }
    }

    delete arr;

    std::cout << std::endl;

    find_eql();

    std::cout << "===============================" << std::endl;

    func1();
}
