#include <iostream>
#include "../LibraryCPPTemplate/array.h"
#include "time.h"
int main()
{
    Array<int>arr(31);
    srand(time(NULL));
    int rain = 0;
    int sum = 0;
    for(int i=0; i<31;i++)
    {
        arr.set(i, rand()%60);
    }
    for(int i=0;i<arr.size();i++)
    {
        if(arr.get(i)>0)
        {
            sum +=arr.get(i);
            rain+=1;
        }
    }
    std::cout <<(double)sum/rain;
}
