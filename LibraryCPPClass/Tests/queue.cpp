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

    std::cout << "\nQueue tests: " << passed << "/4\n";

    return passed == 4 ? 0 : 1;
}
