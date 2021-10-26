#include <iostream>
#include "array.h"
#include "time.h"
int main()
{
    Array<int>arr(31);
    srand(time(NULL));
    int sum = 0;
    int rain = 0;
    int i=0;
    for(i;i<arr.size();i++)
    {
        arr.set(i, rand()%60);
    }

    for(i=0;i<arr.size();i++)
    {
        if(arr.get(i)>0)
        {
            sum +=arr.get(i);
            rain+=1;
        }
    }
    std::cout <<(double)sum/rain;
}
