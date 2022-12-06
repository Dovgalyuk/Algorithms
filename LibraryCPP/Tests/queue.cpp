#include <iostream>
#include "queue.h"

int main()
{
    Queue *queue = queue_create();
    queue_delete(queue);
}
