/*Написать две функции для обработки массива из следующих пунктов и вызвать их из функции main.
Ввести целое число с клавиатуры, создать массив такой размерности и заполнить его случайными числами. Найти количество элементов, значение которых больше среднего арифметического минимального и максимального элементов массива, и напечатать их номера.
Ввести целое число с клавиатуры, создать массив такой размерности и заполнить его случайными числами. Найти пять соседних элементов, сумма значений которых максимальна.*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Array_f(FILE *file)
{
    printf("\ntest number 1\n");
    
    int size;
    fscanf(file,"%d", &size);
        int *a = malloc(size * sizeof(int));

        printf("\nразмер массива - %d\n\n",size);
    
        for (int i = 0; i < size; i ++){
        
            fscanf(file, "%d", &a[i]);
        }   
    
        for (int i = 0; i < size; i++){
        
            printf("a[%d] = %d\n", i, a[i]);
        }
    
    
        free(a); 
    
    return 0;    
}

void Array_random(FILE *file_2)
{
        printf("\ntest number 2\n");
        
    
        srand(time(NULL));

        int size,sum;
        int count = 0;
        int max,min;

        fscanf(file_2,"%d", &size);

    
        int *array_1 = malloc(size * sizeof(int));
 
        max = - 10*1000;
        min =  10*1000;
        sum = 0;

        for (int i = 0; i < size; i ++){
            array_1[i] = rand() % 10 + 1;
        
            if (array_1[i] > max ){
                max = array_1[i];
            }
            else if (array_1[i] < min){
                min = array_1[i];
            }
        }

        sum = (max + min) * 0.5;

        for (int i = 0; i < size; i ++){

            if (array_1[i] > sum){
                count += 1;
                printf("a[%d] = %d\n",i , array_1[i]);
            }
        }
        printf("Полный массив выглядит так:");

        for (int i = 0; i < size; i ++){
            printf(" a[%d] = %d\t",i , array_1[i]);
        }
    
        printf("\nmax_element = %d  and min_element = %d", max, min);
    
        printf("\n");
        printf("число таких элементов: %d\n",count);
    
        free(array_1);
    

}

void Array_sum(FILE *file_3) 
{
    printf("\ntest number 3\n");
    
    
    srand(time(NULL));
    
    int size, max_sum = -10 * 10000000, sum = 0;
    fscanf(file_3,"%d", &size);
    int *array_2 = (int*)malloc(size * sizeof(int));

   
    
    for (int i = 0; i < size; i++) {
        array_2[i] = rand() % 10 + 1; 
        printf("%d\n", array_2[i]);
    }

    for (int i = 0; i <= size - 5; i++) {
        sum = 0;
        for (int j = 0; j < 5; j++) {
            sum += array_2[i + j];
        }
        
        if (sum > max_sum) {
            max_sum = sum;
        }  
    }
    

    printf("\nПолный массив :");
    
    for (int i = 0; i < size; i ++){
        printf("%d ", array_2[i]);
    }
    
    printf("\nМаксимальная сумма пяти соседних элементов: %d\n", max_sum);
    free(array_2);
}

int main(void)
{
    FILE *file = fopen("input_1.txt", "r");
    if (file == NULL) {
    perror("Ошибка открытия файла input_1.txt");
    return 1;
    }
    
    FILE *file_2 = fopen("input_2.txt", "r");
    FILE *file_3 = fopen("input_3.txt", "r");
    
    Array_random(file_2);
    fclose(file_2);
    
    Array_sum(file_3);
    fclose(file_3);
    
    
    Array_f(file);
    fclose(file);

    return 0;
}
