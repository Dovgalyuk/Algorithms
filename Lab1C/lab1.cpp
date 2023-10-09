#include <stdio.h>
#include "array.h"
#include <stdlib.h>

void task1(Array* arr)
{
    // Çàäà÷à 1: â êàêîé ïåðèîä âûïàëî áîëüøå îñàäêîâ: â ïåðâóþ ïîëîâèíó èþíÿ èëè âî âòîðóþ
    int firstHalfSum = 0;
    int secondHalfSum = 0;
    size_t size = array_size(arr);

    for (size_t i = 0; i < size; ++i)
    {
        if (i < size / 2)
        {
            firstHalfSum += array_get(arr, i);
        }
        else
        {
            secondHalfSum += array_get(arr, i);
        }
    }

    if (firstHalfSum > secondHalfSum)
    {
        printf("Áîëüøå îñàäêîâ âûïàëî â ïåðâóþ ïîëîâèíó èþíÿ\n");
    }
    else if (secondHalfSum > firstHalfSum)
    {
        printf("Áîëüøå îñàäêîâ âûïàëî âî âòîðóþ ïîëîâèíó èþíÿ\n");
    }
    else
    {
        printf("Îñàäêè ðàâíîìåðíî ðàñïðåäåëåíû ìåæäó ïåðâîé è âòîðîé ïîëîâèíàìè èþíÿ\n");
    }
}

void task2(Array* arr)
{
    // Çàäà÷à 2: â êàêóþ äåêàäó ìåñÿöà âûïàëî áîëüøå âñåãî îñàäêîâ
    int maxDecadeSum = 0;
    size_t maxDecadeStartIndex = 0;
    size_t size = array_size(arr);

    for (size_t i = 0; i < size; i += 10)
    {
        int decadeSum = 0;
        for (size_t j = i; j < i + 10 && j < size; ++j)
        {
            decadeSum += array_get(arr, j);
        }
        if (decadeSum > maxDecadeSum)
        {
            maxDecadeSum = decadeSum;
            maxDecadeStartIndex = i;
        }
    }

    printf("Äåêàäà ñ íàèáîëüøèì êîëè÷åñòâîì îñàäêîâ: ");
    for (size_t i = maxDecadeStartIndex; i < maxDecadeStartIndex + 10 && i < size; ++i)
    {
        printf("%d ", array_get(arr, i));
    }
    printf("\n");
}

int main()
{
    Array* arr = NULL;
    size_t size;

    // Ââîä ðàçìåðà ìàññèâà ñ êëàâèàòóðû
    printf("Ââåäèòå ðàçìåð ìàññèâà: ");
    scanf("%zu", &size);

    // Ñîçäàíèå ìàññèâà è çàïîëíåíèå åãî ñëó÷àéíûìè äàííûìè
    arr = array_create(size);
    for (size_t i = 0; i < size; ++i)
    {
        array_set(arr, i, rand() % 100); // Ãåíåðàöèÿ ñëó÷àéíîãî ÷èñëà îò 0 äî 99
    }

    // Âûçîâ çàäà÷è 1
    task1(arr);

    // Óäàëåíèå ìàññèâà
    array_delete(arr);

    // Ââîä ðàçìåðà íîâîãî ìàññèâà ñ êëàâèàòóðû
    printf("Ââåäèòå ðàçìåð íîâîãî ìàññèâà: ");
    scanf("%zu", &size);

    // Ñîçäàíèå íîâîãî ìàññèâà è çàïîëíåíèå åãî ñëó÷àéíûìè äàííûìè
    arr = array_create(size);
    for (size_t i = 0; i < size; ++i)
    {
        array_set(arr, i, rand() % 100); // Ãåíåðàöèÿ ñëó÷àéíîãî ÷èñëà îò 0 äî 99
    }

    // Âûçîâ çàäà÷è 2
    task2(arr);

    // Óäàëåíèå âòîðîãî ìàññèâà
    array_delete(arr);

    return 0;
}
