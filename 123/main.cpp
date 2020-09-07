#include <iostream>
#include <ctime>
#include "array.h"

int main()
{
    size_t size;
    std::cin >> size;
    Array *arr = array_create(size);

    srand(time(0));
    for (int i = 0 ; i < size; i++)
    {
        array_set(arr, i, rand()%10-5);
        std::cout<< array_get(arr, i)<<" ";
    }
    std::cout << std::endl;


    int num = array_get(arr, 0);
    int max_number_of_repetitions = 1;
    int number_of_repetitions;

    for (int i = 0; i < size; i++)
    {
        number_of_repetitions = 1;
        for (int k = i + 1; k < size; k++)
        {
            if (array_get(arr,i) == array_get(arr,k))
                number_of_repetitions += 1;
        }
        if(number_of_repetitions > max_number_of_repetitions)
        {
            max_number_of_repetitions = number_of_repetitions;
            num = array_get(arr, i);
        }
    }

    if (max_number_of_repetitions > 1)
    {
        std::cout << std::endl << num <<" meet "<< max_number_of_repetitions;
    }
    else
    {
        std::cout << "no repetitions";
    }
    std::cout << std::endl;
    array_delete(arr);
    system("pause");

	return 0;
}
