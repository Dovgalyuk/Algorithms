
#define _CRT_SECURE_NO_WARNINGS
#include "array.h"
#include <stdio.h>
#include <iostream>


using namespace std;
int a;


void task1(Array* arr)
{
    
    int sumosadkov = 0;
    for (int i = 0; i <a; i++)
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
    int c, z, x;
    c = 0;
    for (int i = 0; i < a; i++)
    {
        if (*(int*)(array_get(arr, i)) > 0)
        {
            for (int j = i + 1; j < a; j++)
                if (*(int*)(array_get(arr, i)) == *(int*)(array_get(arr, j)))
                {
                    c += 1;
                    z = *(int*)(array_get(arr, i));
                    *(int*)(array_get(arr, j)) = -1;
                }
            if (c == 1)
            {
                
                printf("%i", z);
                printf("%s", "\t");
                
            }
        }
        c = 0;
    }
}

int main()
{
   
    Array* arr = NULL;
    scanf("%d", &a);
    
    arr = array_create(a, NULL);
    for (int i = 0; i < a; i++)
    {
        int* p = (int*)malloc(sizeof(int)); 
        *p = rand();
        array_set(arr, i, p);
    }
    /* Create array here */
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    scanf("%i", &a);
    arr = array_create(a, NULL);
    for (int i = 0; i < a; i++)
    {
        int* p = (int*)malloc(sizeof(int));
        *p = rand();
        array_set(arr, i, p);
    }
    task2(arr);
    array_delete(arr);

   
    
   

  
   
   

    

   
   
    
    
    
    
}