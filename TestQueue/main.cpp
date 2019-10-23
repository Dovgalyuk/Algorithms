#include <iostream>
#include "queue.h"

int main()
{
    Queue *queue = queue_create();

    queue_insert(queue, 1);
    queue_insert(queue, 2);
    queue_insert(queue, 3);
	//queue_insert(queue, 5);
	//queue_insert(queue, 6);
	//queue_insert(queue, 7);
	//queue_insert(queue, 8);

    if (queue_get(queue) != 1)
        std::cout << "Invalid first element of the queue\n";

    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_remove(queue);

    if (queue_get(queue) != 2)
        std::cout << "Invalid second element of the queue\n";

    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_remove(queue);

	if (queue_get(queue) != 3)
		std::cout << "Invalid second element of the queue\n";

	std::cout << "Get: " << queue_get(queue) << "\n";
   
    queue_insert(queue, 4);
    while (!queue_empty(queue))
    {
        std::cout << "Get: " << queue_get(queue) << "\n";
        queue_remove(queue);
    }

	/*std::cout << "\n";
	queue_insert(queue, 1);
	queue_insert(queue, 2);
	queue_insert(queue, 3);
	queue_insert(queue, 4);
	queue_insert(queue, 5);
	queue_insert(queue, 6);
	queue_insert(queue, 7);
	queue_insert(queue, 8);

	while (!queue_empty(queue))
	{
		std::cout << "Get: " << queue_get(queue) << "\n";
		queue_remove(queue);
	}*/

    queue_delete(queue);
}