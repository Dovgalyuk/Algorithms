
#define _CRT_SECURE_NO_WARNINGS
#include "array.h"
#include <stdio.h>
#include <stdlib.h>



void task1(Array* arr)
{
    
    int sumosadkov = 0;
    for (size_t i = 0; i < array_size(arr); i++)
    {
        sumosadkov += *(int*)(array_get(arr, i));
        
        if ((i+1) % 30 == 0)
        {
            
            printf("%i", sumosadkov);
            printf("%s", "\t");
            sumosadkov = 0;
        }
    }
	
}



void task2(Array* arr)
{
    size_t c, z;
    
    for (size_t i = 0; i < array_size(arr); i++)
    {
        c = 0;
        if (*(int*)(array_get(arr, i)) >= 0)
        {
            for (size_t j = 0; j < array_size(arr); j++)
           
                
               
                if (*(int*)(array_get(arr, i)) == *(int*)(array_get(arr, j)))
                {
                    

                    c += 1;

                    z = *(int*)(array_get(arr, i));
                    if (i != j)
                    {
                        int* p = (int*)malloc(sizeof(int));
                        *p = -1;
                        array_set(arr, j, p);
                    }

                }
            
            if (c == 2)
            {
                
                printf("%zi", z);
                printf("%s", "\t");
                
            }
        }
        
    }

}

int main()
{
   size_t a;
    Array* arr = NULL;
    scanf("%zd", &a);
    
    arr = array_create(a, NULL);
    for (size_t i = 0; i < a; i++)
    {
        int* p = (int*)malloc(sizeof(int)); 
        *p = rand();
        array_set(arr, i, p);
    }
    /* Create array here */
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    scanf("%zi", &a);
    arr = array_create(a, NULL);
    for (size_t i = 0; i < a; i++)
    {
       int* p = (int*)malloc(sizeof(int));
        
        *p = rand();
        array_set(arr, i, p);
        
        
    }
    

    task2(arr);
    array_delete(arr);


}



