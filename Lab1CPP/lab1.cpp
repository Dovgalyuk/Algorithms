#include "lab1.h"
#include <cstdio>
#include <stdio.h>
Array *array_create_and_read(FILE *input)
{
    int n;
    if (fscanf(input, "%d", &n) < 0)
    {
        return nullptr;
    }
    Array *arr = new Array(n);
    for (int i = 0; i < n; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) < 0)
        {
            delete arr;
            return nullptr;
        }
        arr->set(i, x);
    }
    return arr;
}

std::vector<Data> task1(Array *arr)
// найти в массиве элементы, меньшие чем среднее арифметическое среди всех чисел массива
{
    std::vector<Data> ans;
    Data sum = 0;
    for (size_t i = 0; i < arr->size(); i++)
    {
        sum += arr->get(i);
    }

    double average = double(sum) / double(arr->size());
    for (size_t i = 0; i < arr->size(); i++)
    {
        if (double(arr->get(i)) < average)
        {
            ans.push_back(arr->get(i));
        }
    }
    return ans;
}
std::vector<Data> task2(Array *arr)
// найти в массиве элементы, которые не делятся ни на какие другие элементы этого массива
{
    std::vector<Data> ans;
    enum Status
    {
        NotExist = 0, // число еще не внесено
        Wrong = 1,    // число не войдет в ответ
        Pass = 2      // число войдет в ответ
    };
    std::unordered_map<Data, Status> m;
    for (size_t i = 0; i < arr->size(); i++)
    /*проходясь по каждому элементу, проверяем его с каждым числом до него.
    таким образом, после каждой итерации цикла в m будет лежать ответ для отрезка массива
    arr[0:i], соответственно, после окончания цикла мы получим ответ для всего массива*/
    {
        auto current = arr->get(i);
        if (m[current] == Pass) // если элемент в массиве "парный", то он всегда не входит в ответ, т.к. эти два
                                // элемента делятся друг на друга
        {
            m[current] = Wrong;
        }
        for (size_t j = 0; j < i; j++)
        {
            auto subEl = arr->get(j);
            if (subEl != current)
            {
                /*выбираем большее и меньшее для двух сравниваемых чисел. Если большее не делится на меньшее, то вносим
                 его в ответ, при условии, что оно в статусе NotExist
                 Если же оно делится, то ставим большему числу статус Wrong, в ответ не попадет*/
                int max = subEl > current ? subEl : current;
                int min = subEl < current ? subEl : current;
                if (min != 0 &&
                    max % min == 0) // TODO тут вопрос, что делать, при делении на 0. Сейчас решил, что 0 мы игнорируем
                {
                    m[max] = Wrong;
                }
                else if (m[max] == NotExist)
                {
                    m[max] = Pass;
                }
            }
        }
    }

    for (auto const &val : m) // фильтруем ответ, оставляя только те числа, которые ни на что не делятся
    {
        if (val.second == Pass)
        {
            ans.push_back(val.first);
        }
    }
    return ans;
}

int main(int argc, char **argv)
{
    FILE *input;
    if (argc <= 1)
    {
        input = stdin;
    }
    else
    {
        input = fopen(argv[1], "r");
    }

    Array *arr = array_create_and_read(input);
    task1(arr);
    task2(arr);

    delete arr;
    fclose(input);
    return 0;
}
