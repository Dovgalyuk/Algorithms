
#include <iostream>
#include <stdexcept>
#include "queue.h"

int main()
{
    int passed = 0;

    {
        Queue queue;

        queue.insert(1);
        queue.insert(2);
        queue.insert(3);

        if (queue.get() == 1)
        {
            queue.remove();

            if (queue.get() == 2)
            {
                queue.remove();

                if (queue.get() == 3)
                {
                    passed++;
                    std::cout << "[PASSED] Queue FIFO order\n";
                }
            }
        }
        else
        {
            std::cout << "[FAILED] Queue FIFO order\n";
        }
    }

    {
        Queue queue;
        queue.insert(10);
        queue.insert(20);

        Queue copy(queue);
        Queue assigned;
        assigned = queue;

        queue = queue;

        if (copy.get() == 10 &&
            assigned.get() == 10 &&
            queue.get() == 10)
        {
            passed++;
            std::cout << "[PASSED] Queue copy and assignment\n";
        }
        else
        {
            std::cout << "[FAILED] Queue copy and assignment\n";
        }
    }

    {
        Queue queue;

        for (int i = 1; i <= 4; i++)
            queue.insert(i);

        queue.remove();
        queue.remove();

        queue.insert(5);
        queue.insert(6);
        queue.insert(7);

        bool correct = true;

        for (int expected = 3; expected <= 7; expected++)
        {
            if (queue.get() != expected)
            {
                correct = false;
                break;
            }

            queue.remove();
        }

        if (correct)
        {
            passed++;
            std::cout << "[PASSED] Queue circular buffer and growth\n";
        }
        else
        {
            std::cout << "[FAILED] Queue circular buffer and growth\n";
        }
    }

    {
        Queue queue;
        bool getException = false;
        bool removeException = false;

        try
        {
            queue.get();
        }
        catch (const std::underflow_error&)
        {
            getException = true;
        }

        try
        {
            queue.remove();
        }
        catch (const std::underflow_error&)
        {
            removeException = true;
        }

        if (getException && removeException)
        {
            passed++;
            std::cout << "[PASSED] Queue empty exception\n";
        }
        else
        {
            std::cout << "[FAILED] Queue empty exception\n";
        }
    }

    {
        Queue* queue = new Queue();

        queue->insert(1);
        queue->insert(2);
        queue->insert(3);

        *queue = *queue;

        if (queue->get() != 1)
        {
            std::cout << "Invalid first element of the queue\n";
            return 1;
        }

        std::cout << "Get: " << queue->get() << "\n";
        queue->remove();

        if (queue->get() != 2)
        {
            std::cout << "Invalid second element of the queue\n";
            return 1;
        }

        std::cout << "Get: " << queue->get() << "\n";
        queue->remove();

        if (queue->get() != 3)
        {
            std::cout << "Invalid third element of the queue\n";
            return 1;
        }

        std::cout << "Get: " << queue->get() << "\n";
        queue->insert(4);

        while (!queue->empty())
        {
            std::cout << "Get: " << queue->get() << "\n";
            queue->remove();
        }

        queue->insert(0);

        for (int i = 1; i <= 1000000; ++i)
        {
            queue->insert(i);
        }

        for (int i = 1; i <= 1000000; ++i)
        {
            queue->remove();
        }

        for (int i = 1; i <= 1000000; ++i)
        {
            queue->insert(i);
            queue->remove();
        }

        delete queue;

        queue = new Queue();
        queue->insert(0);

        for (int i = 1; i <= 100000; ++i)
        {
            int cnt = 1 + i % 20;

            for (int j = 0; j < cnt; ++j)
            {
                queue->insert(i);
            }

            for (int j = 0; j < cnt; ++j)
            {
                queue->remove();
            }
        }

        delete queue;
    }

    std::cout << "\nQueue tests: " << passed << "/4\n";

    return passed == 4 ? 0 : 1;
}
