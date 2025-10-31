#include <stdio.h>
#include <locale.h>
#include "../../LibraryC/array.h"

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    Array* arr = array_create(5);
    
    for (int i = 0; i < 5; i++) {
        array_set(arr, i, (i + 1) * 10);
    }
    
    printf("Элементы массива: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", array_get(arr, i));
    }
    printf("\n");
    
    array_destroy(arr);
    return 0;
}