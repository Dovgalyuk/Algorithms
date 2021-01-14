#include <fstream>
#include <vector>
#include "Vector.h"
#include "Queue.h"

void testQueue();

void lab();

void testVector(){
    Vector<int> vector = Vector<int>();
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    vector.print();
    vector[1] = -5;
    vector.print();
    vector.erase(2);
    vector.print();
}

int main() {
    //testQueue();
    //testVector();
    lab();

    return 0;
}

void lab() {
    //[input_file_stream] - поток считывания из файла.
    std::ifstream input_file_stream("input.txt");
    //Проверка, удалось ли открыть файл.
    if (!input_file_stream){
        std::cerr << "File \"input.txt\" missing" << std::endl;
    }
    //[output_file_stream] - поток считывания из файла.
    std::ofstream output_file_stream("output.txt");
    //Проверка, удалось ли открыть файл.
    if (!input_file_stream){
        std::cerr << "File \"output.txt\" missing" << std::endl;
    }
    //Очередь, для обхода графа.
    Queue<int> queue;


    //Размер матрицы смежности.
    size_t size;
    //Считывание этого размера из файла.
    input_file_stream >> size;
    //Вектор с вершинами, где i-й элемент равен растоянию от указаной вершины до вершины i.
    Vector<int> viseted = Vector<int>(size);

    //Инициализация матрицы смежности.
    int** matrix = new int*[size];
    //И её заполнение, путём считывания с файла.
    for (size_t i = 0; i < size; ++i){
        matrix[i] = new int[size];
        for (size_t j = 0; j < size; ++j){
            input_file_stream >> matrix[i][j];
        }
    }
    //Заполнение вектора расстояний -1-ми, что эквивалентно тому, что на данном этапе мы не имеем никакой информации о длине маршрута
    for (int l = 0; l < 4; ++l) {
        viseted.push_back(-1);
    }
    //...кроме маршрута из начальной точки в неё саму. Разумеется, эта длина равна нулю.
    viseted[0] = 0;

    //Добавляем в очередь начальную точку.
    queue.insert(0);
    //Пока очередь не пуста...
    while(!queue.empty()){
        //Берём первый элемент из очереди...
        int u = queue.get();
        //Удаляем его из очереди...
        queue.remove();
        //Проходим по матрице смежности...
        for (int j = 0; j < size; j++) {
            int v = matrix[u][j];
            //Если между этой точкой и другой есть связь... (выраженная через положительное ненулевое значение)
            //И, если расстояние до неё ещё не вычислено...
            if (v > 0 && viseted[j] == -1) {
                //Записываем расстояние до этого соседа...
                viseted[j] = viseted[u] + 1;
                //И добавляем его в очередь.
                queue.insert(j);
            }
        }
    }
    //Выводим результат в файл.
    for (size_t k = 0; k < size; ++k) {
        output_file_stream << viseted[k] << std::endl;
    }
    //Закрываем потоки ввода-вывода, перед завершением работы.
    input_file_stream.close();
    output_file_stream.close();
}

void testQueue() {
    Queue<int> queue;
    queue.insert(1);
    queue.insert(2);
    queue.insert(3);

    if (queue.get() != 1)
        std::cout << "Invalid first element of the queue\n";

    std::cout << "Get: " << queue.get() << "\n";
    queue.remove();

    if (queue.get() != 2)
        std::cout << "Invalid second element of the queue\n";

    std::cout << "Get: " << queue.get() << "\n";
    queue.remove();

    if (queue.get() != 3)
        std::cout << "Invalid third element of the queue\n";

    std::cout << "Get: " << queue.get() << "\n";
    queue.insert(4);
    while (!queue.empty())
    {
        std::cout << "Get: " << queue.get() << "\n";
        queue.remove();
    }
}
