// Дополнительный тест очереди №2: вставка и удаление вперемешку
#include <iostream>
#include "queue.h"

int fail(const char *msg)
{
    std::cout << "Error: " << msg << "\n";
    return 1;
}

int main()
{
    Queue *queue = queue_create();

    // вставка и удаление вперемешку
    queue_insert(queue, 1);
    queue_insert(queue, 2);
    queue_remove(queue);          // ушла 1
    queue_insert(queue, 3);
    if (queue_get(queue) != 2)
        return fail("mixed insert/remove");
    queue_remove(queue);          // ушла 2
    if (queue_get(queue) != 3)
        return fail("mixed insert/remove");
    queue_remove(queue);          // ушла 3
    if (!queue_empty(queue))
        return fail("queue must be empty");

    // отрицательные числа и ноль
    queue_insert(queue, -7);
    queue_insert(queue, 0);
    if (queue_get(queue) != -7)
        return fail("negative value");
    queue_remove(queue);
    if (queue_get(queue) != 0)
        return fail("zero value");
    queue_remove(queue);

    // удаляем непустую очередь (утечки поймает санитайзер)
    for (int i = 0; i < 1000; i++)
        queue_insert(queue, i);
    queue_delete(queue);

    std::cout << "Queue mixed test passed\n";
    return 0;
}
