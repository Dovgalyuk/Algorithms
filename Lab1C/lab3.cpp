/*
»меетс€ поток за€вок дл€ трех очередей. «а€вки отсортированы по времени поступлени€ в каждую очередь.
Ќаписать программу, печатающую пор€док, в котором эти за€вки будут обслужены. ¬рем€ обслуживани€ всех за€вок одинаковое. 
‘ормат входного файла: количество за€вок в первой очереди, список моментов времени в которые они возникают; аналогично дл€ второй и третей очередей.
¬ выходной файл дл€ каждой обслуженной за€вки печатаетс€ номер очереди и врем€ прихода за€вки.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include "queue.h"

using namespace std;

struct Request
{
    int queueNum;
    int arrivalTime;
};

void processRequests(const vector<Queue*>& queues, ofstream& output)
{
    vector<Request> processedRequests;
    int currentTime = 0;

    while (true)
    {
        int minQueueNum = 0;
        int minQueueRequest = INT_MAX;

        // Find the queue and request with the earliest arrival time
        for (size_t i = 0; i < queues.size(); i++)
        {
            if (!queue_empty(queues[i]))
            {
                int request = queue_get(queues[i]);
                if (request <= currentTime && request < minQueueRequest)
                {
                    minQueueNum = i + 1;
                    minQueueRequest = request;
                }
            }
        }

        // Break the loop if all queues are empty
        if (minQueueNum == 0)
            break;

        // Process the earliest request from the selected queue
        processedRequests.push_back({ minQueueNum, minQueueRequest });
        queue_remove(queues[minQueueNum - 1]);

        currentTime++;
    }

    for (const auto& request : processedRequests)
    {
        output << request.queueNum << " " << request.arrivalTime << endl;
    }
}

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    vector<Queue*> queues;

    for (int i = 0; i < 3; i++)
    {
        int requestCount;
        input >> requestCount;

        Queue* queue = queue_create();

        for (int j = 0; j < requestCount; j++)
        {
            int arrivalTime;
            input >> arrivalTime;
            queue_insert(queue, arrivalTime);
        }

        queues.push_back(queue);
    }

    processRequests(queues, output);

    for (auto queue : queues)
    {
        queue_delete(queue);
    }

    input.close();
    output.close();

    return 0;
}