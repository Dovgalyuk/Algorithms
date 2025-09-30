#include <fstream>
#include <iostream>
#include "array.h"
using namespace std;

Array readArrayFromFile(const string& fileName)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error reading the file" << endl;
        return Array(0);
    }
    
    size_t n;
    file >> n;
    Array arr(n);
    for (size_t i = 0; i < n; i++)
    {
        Data val;
        file >> val;
        arr.set(i, val);
    }

    file.close();
    return arr;
}

void subtractingArray(const string& fileName)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error reading the file" << endl;
        return;
    }
    
    size_t n, k1, k2;
    file >> n;
    Array arr(n);
    for (size_t i = 0; i < n; i++)
    {
        Data val;
        file >> val;
        arr.set(i, val);
    }
    file >> k1;
    file >> k2;
    file.close();
      
    if (arr.size() == 0 || k1 > n || k2 > n)
    {
        return;
    }
    
    cout << "K1: "<< arr.get(k1) <<"; K2: "<< arr.get(k2) << endl;
    cout << "Array before subtraction: " << endl;
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr.get(i) << " ";
    }
    cout << endl;

    for (size_t i = 0; i < arr.size(); i++)
    {
        if (arr.get(i) > 0)
        {
            arr.set(i, arr.get(i) - arr.get(k1));
        }
        else
        {
            arr.set(i, arr.get(i) + arr.get(k2));
        }
    }
    
    cout << "Array after subtraction: " << endl;
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr.get(i) << " ";
    }
    cout << endl;
       
}

void swap(Array &numbers, size_t first, size_t second)  
{  
    int temp{numbers.get(first)};  
    numbers.set(first,numbers.get(second));  
    numbers.set(second,temp);
}

void sort(Array &numbers, size_t start, size_t end)  
{  
    if (start >= end)  
        return;  
    
    size_t current {start};  
    
    for (size_t i {start + 1}; i <= end; i++)  
    {        
        if (numbers.get(i) < numbers.get(start))   
        {  
            swap(numbers, ++current, i);  
        }    
    }   
    swap(numbers, start, current);  
    if (current > start)   
    {  
        sort(numbers, start, current - 1);  
    }    
    if (end > current + 1)   
    {  
        sort(numbers, current + 1, end);  
    }
}  

void frequentNumber(const string& fileName)
{
    Array arr = readArrayFromFile(fileName);
    if (arr.size() == 0)
    {
        return;
    }

    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr.get(i) << " ";
    }
    cout << endl;

    sort(arr, 0, arr.size() - 1);

    size_t maxCount = 1;
    size_t frequintNumberID = 0;
    size_t currentCount = 1;
    
    for (size_t i = 1; i < arr.size(); i++)
    {
        if (arr.get(i-1) == arr.get(i))
        {
            currentCount++;
            if (currentCount > maxCount)
            {
                maxCount = currentCount;
                frequintNumberID = i;
            }
        }
        else
        {
            currentCount = 1;
        }
    }
    cout <<"FrequintNumber: "<<arr.get(frequintNumberID)<< endl;
}


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Help: "<<argv[0]<<"\n -sub <fileName> -- Subtracting k1 from positive numbers and subtracting k2 from the remaining numbers\n"
                                   " -freq <fileName> -- The most frequent number in the array"<<endl;
        
        return 1;
    }

    
    string mode = argv[1];

    if (mode == "-sub")
    {
        subtractingArray(argv[2]);
    }
    else if (mode == "-freq")
    {
        frequentNumber(argv[2]);
    }
    else
    {
        return 1;
    }

    return 0;
}