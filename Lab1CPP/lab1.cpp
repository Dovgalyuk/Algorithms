        #include <cstdio>
        #include <stdexcept>
        #include "array.h"
        #include <unordered_map>
        using namespace std;


        Array* array_create_and_read(FILE* input)
        {
            int n;
            if (fscanf(input, "%d", &n) < 1) throw std::invalid_argument("Failed to read size");
            /* Create array */
            Array* arr = array_create(n);
            /* Read array data */
            for (int i = 0; i < n; ++i)
            {
                int x;
                if (fscanf(input, "%d", &x) < 1) throw std::invalid_argument("Failed to read number");
                array_set(arr, i, x);
            }

            return arr;
        }

        void task1(Array* arr)
        {
            size_t size = array_size(arr);
            int k1, k2;
            scanf("%d %d", &k1, &k2);
            for (size_t index{ 0 }; index < size; ++index) {
                if(array_get(arr, index) >= 0){
                    array_set(arr, index, array_get(arr, index)-k1);
                } else {
                    array_set(arr, index, array_get(arr, index)-k2);
                }
            }
            for (size_t index{ 0 }; index < size; ++index) {
                printf("%d", array_get(arr, index));
            }
            printf("\n");
        }

        void task2(Array* arr)
        {
            unordered_map<int, int> frequency_map;
            size_t size = array_size(arr);
            // Подсчет частоты появления каждого числа
            for (size_t i = 0; i < size; ++i) {
                int value = array_get(arr, i);
                frequency_map[value]++;
            }

            // Определение числа с максимальной частотой
            int most_frequent_number = 0;
            int max_frequency = 0;

            for (const auto& pair : frequency_map) {
                if (pair.second > max_frequency) {
                    max_frequency = pair.second;
                    most_frequent_number = pair.first;
                }
            }
            printf("%d", most_frequent_number);

        }

        int main(__attribute__((unused)) int argc, char** argv)
        {
            Array* arr = NULL;
            FILE* input = fopen(argv[1], "r");
            arr = array_create_and_read(input);
            task1(arr);
            array_delete(arr);
            /* Create another array here */
            arr = array_create_and_read(input);
            task2(arr);
            array_delete(arr);  
            fclose(input);
            return 0;
        }
        