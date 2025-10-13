    #include <iostream>
    #include <fstream>
    #include "array.h"


    Array *array_create_and_read(std::ifstream &input)
    {
        int n;
        input >> n;
        
        Array* arr = array_create(n);
    
        for(int i = 0; i < n; i++)
        { 
            int x;
            input >> x;
            array_set(arr, i, x);
        }
        return arr;
    }

    void task1(Array *arr)
    { 
        int arrSize = array_size(arr);
        int decade = arrSize / 3;
        int firstHalf = 0;
        int secondHalf = 0;
        int firstDecade = 0;
        int secondDecade = 0;
        int thirdDecade = 0;
        for(int i = 0; i < arrSize/2; i++)
        {
            firstHalf += array_get(arr, i);
        }     
        for(int i = arrSize/2; i < arrSize; i++)
        {
            secondHalf += array_get(arr, i);
        }
        for(int i = 0; i < decade; i++){
            firstDecade += array_get(arr, i);
        }
        for(int i = decade; i < decade*2; i++){
            secondDecade += array_get(arr, i);
        }
        for(int i = decade*2; i < decade*3; i++){
            thirdDecade += array_get(arr, i);
        }
        std::cout << "In the first half of June, " <<  firstHalf <<" mm of precipitation fell.\n";
        std::cout << "In the second half of June, " <<  secondHalf <<" mm of precipitation fell.\n";
        std::cout << firstDecade << " mm of precipitation fell in the first decade of June.\n";
        std::cout << secondDecade << " mm of precipitation fell in the second decade of June.\n";
        std::cout << thirdDecade << " mm of precipitation fell in the third decade of June.\n";
        if(firstHalf>secondHalf){
            std::cout << "As a result, more precipitation fell in the first half of June.\n";
        }
        else if(firstHalf<secondHalf){
            std::cout << "As a result, more precipitation fell in the second half of June.\n";
        }
        else{
            std::cout << "The same amount of precipitation fell in each half of the month.\n";
        }
         if (firstDecade > secondDecade && firstDecade > thirdDecade)
        {
            std::cout << "The first decade of June saw the most precipitation.\n";
        }
        else if(secondDecade > firstDecade && secondDecade > thirdDecade)
        {
            std::cout << "The second decade of June saw the most precipitation.\n";
        }
        else if(thirdDecade > firstDecade && thirdDecade > secondDecade)
        {
            std::cout << "The third decade of June saw the most precipitation.\n";
        }
        else
        {
            std::cout << "The same amount of precipitation fell in each decade of the month.\n";
        }
    }

void task2(Array *arr)
{
    int size = array_size(arr);    
    bool found = false;
    std::cout << "Elements that occur 2 times: ";
    for (int i = 0; i < size; i++) 
    {
        Data current = array_get(arr, i);
        int count = 0;
        int firstIndex = size;
        for (int j = 0; j < size; j++) {
            if (array_get(arr, j) == current) 
            {
                count++;
                if (firstIndex == size) 
                {
                    firstIndex = j;
                }
            }
        }
        if (count == 2 && firstIndex == i) 
        {
            if (found) {
                std::cout << " ";
            }
            std::cout << current;
            found = true;
        }
    }
    if (!found) 
    {
        std::cout << "no such elements";
    }
    std::cout << std::endl;
}

    int main(int argc, char **argv)
    { 
        Array *arr = NULL;
        std::ifstream input(argv[1]);
        arr = array_create_and_read(input);
        task1(arr);
        array_delete(arr);
        /* Create another array here */
        arr = array_create_and_read(input);
        task2(arr);
        array_delete(arr);
        input.close();
    }