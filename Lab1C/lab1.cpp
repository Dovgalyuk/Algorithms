#include <stdio.h>  
#include <stdio.h> 

int main() {
    int Y[24];
    int Q[6][4];
    int i, j;
    int count = 0;

    printf("Введите элементы массива Y:\n");

    for (i = 0; i < 24; i++) {
        scanf("%d", &Y[i]);
    }

    printf("\nМассив Y:\n");

    for (i = 0; i < 24; i++) {
        printf("%d ", Y[i]);

        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }

    printf("\n\nМатрица Q:\n");

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 4; j++) {
            Q[i][j] = Y[count];
            count++;
            printf("%d ", Q[i][j]);
        }
        printf("\n");
    }

    return 0;
}