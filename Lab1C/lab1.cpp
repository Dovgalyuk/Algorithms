#include <stdio.h>
#include "array.h"

void task1(Array* arr)
{
    // ������ 1: � ����� ������ ������ ������ �������: � ������ �������� ���� ��� �� ������
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
        printf("������ ������� ������ � ������ �������� ����\n");
    }
    else if (secondHalfSum > firstHalfSum)
    {
        printf("������ ������� ������ �� ������ �������� ����\n");
    }
    else
    {
        printf("������ ���������� ������������ ����� ������ � ������ ���������� ����\n");
    }
}

void task2(Array* arr)
{
    // ������ 2: � ����� ������ ������ ������ ������ ����� �������
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

    printf("������ � ���������� ����������� �������: ");
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

    // ���� ������� ������� � ����������
    printf("������� ������ �������: ");
    scanf("%zu", &size);

    // �������� ������� � ���������� ��� ���������� �������
    arr = array_create(size);
    for (size_t i = 0; i < size; ++i)
    {
        array_set(arr, i, rand() % 100); // ��������� ���������� ����� �� 0 �� 99
    }

    // ����� ������ 1
    task1(arr);

    // �������� �������
    array_delete(arr);

    // ���� ������� ������ ������� � ����������
    printf("������� ������ ������ �������: ");
    scanf("%zu", &size);

    // �������� ������ ������� � ���������� ��� ���������� �������
    arr = array_create(size);
    for (size_t i = 0; i < size; ++i)
    {
        array_set(arr, i, rand() % 100); // ��������� ���������� ����� �� 0 �� 99
    }

    // ����� ������ 2
    task2(arr);

    // �������� ������� �������
    array_delete(arr);

    return 0;
}