/*
»меетс€ поток за€вок дл€ трех очередей. «а€вки отсортированы по времени поступлени€ в каждую очередь.
Ќаписать программу, печатающую пор€док, в котором эти за€вки будут обслужены. ¬рем€ обслуживани€ всех за€вок одинаковое. 
‘ормат входного файла: количество за€вок в первой очереди, список моментов времени в которые они возникают; аналогично дл€ второй и третей очередей.
¬ выходной файл дл€ каждой обслуженной за€вки печатаетс€ номер очереди и врем€ прихода за€вки.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "queue.h"

using namespace std;

struct Request
{
    int queueNum;
    int arrivalTime;
};

void processRequests(const vector<vector<int>>& queues, ofstream& output)
{
    Queue* queue1 = queue_create();
    Queue* queue2 = queue_create();
    Queue* queue3 = queue_create();

    vector<Request> processedRequests;

    for (int i = 1; i <= 3; i++)
    {
        for (int arrivalTime : queues[i - 1])
        {
            switch (i)
            {
            case 1:
                queue_insert(queue1, arrivalTime);
                break;
            case 2:
                queue_insert(queue2, arrivalTime);
                break;
            case 3:
                queue_insert(queue3, arrivalTime);
                break;
            }
        }
    }

    int currentTime = 0;

    while (!queue_empty(queue1) || !queue_empty(queue2) || !queue_empty(queue3))
    {
        int minQueueNum = 0;

        // Find the queue with the earliest request
        if (!queue_empty(queue1))
        {
            if (queue_get(queue1) <= currentTime)
                minQueueNum = 1;
        }

        if (!queue_empty(queue2))
        {
            int queue2Request = queue_get(queue2);
            if (queue2Request < queue_get(queue1) || minQueueNum == 0)
                minQueueNum = 2;
        }

        if (!queue_empty(queue3))
        {
            int queue3Request = queue_get(queue3);
            if (queue3Request < queue_get(queue1) || minQueueNum == 0 || queue3Request < queue_get(queue2))
                minQueueNum = 3;
        }

        // Process the earliest request from the selected queue
        switch (minQueueNum)
        {
        case 1:
            processedRequests.push_back({ 1, queue_get(queue1) });
            queue_remove(queue1);
            break;
        case 2:
            processedRequests.push_back({ 2, queue_get(queue2) });
            queue_remove(queue2);
            break;
        case 3:
            processedRequests.push_back({ 3, queue_get(queue3) });
            queue_remove(queue3);
            break;
        }

        currentTime++;
    }

    for (const auto& request : processedRequests)
    {
        output << request.queueNum << " " << request.arrivalTime << endl;
    }

    queue_delete(queue1);
    queue_delete(queue2);
    queue_delete(queue3);
}

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    vector<vector<int>> queues;

    for (int i = 0; i < 3; i++)
    {
        int requestCount;
        input >> requestCount;

        vector<int> queueRequests(requestCount);

        for (int j = 0; j < requestCount; j++)
        {
            input >> queueRequests[j];
        }

        queues.push_back(queueRequests);
    }

    processRequests(queues, output);

    input.close();
    output.close();

    return 0;
}